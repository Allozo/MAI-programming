import os
import time
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options as ChromeOptions
from selenium.webdriver.common.action_chains import ActionChains
import urllib.request
import threading
from PIL import Image
from io import BytesIO


class DownloadWebsite:
    def __init__(self):
        # перечислим все сайты, откуда будем брать информацию
        self.__url_tvway = 'http://tvway.ru/'
        self.__url_world_cam = 'https://world-cam.ru/'

        # тут пудет словарь {категория <-> ссылка на категории}
        self.category = dict()

        driver_path = os.getcwd() + '/chromedriver'
        self.wdriver = webdriver.Chrome(executable_path=driver_path)
        # self.__update_category()

    def print_all_list_category_and_url(self):
        for line in sorted(self.category):
            # print(line, self.list_category[line])
            for url in self.category[line]:
                print('{0:.<25} {1}'.format(line, url))

    def print_category(self):
        for i in sorted(self.category):
            print(i)

    def __print_on_value(self, value):
        if value not in self.category:
            print(f'По запросу "{value}" ничего не найдено.\n')
            return
        print(f'Для запроса "{value}" найдено:')
        for i in self.category[value]:
            print(i)
        print('\n')

    def __add_to_list(self, key, value):
        if key in self.category:
            self.category[key.lower()].append(value.lower())
        else:
            self.category[key.lower()] = [value.lower()]

    def __get_attributes(self, element):
        return self.wdriver.execute_script(
            """
            let attr = arguments[0].attributes;
            let items = {}; 
            for (let i = 0; i < attr.length; i++) {
                items[attr[i].name] = attr[i].value;
            }
            return items;
            """,
            element
        )

    def __take_screenshot(self, element, path):
        location = element.location_once_scrolled_into_view
        size = element.size
        png = self.wdriver.get_screenshot_as_png()  # saves screenshot of entire page

        im = Image.open(BytesIO(png))  # uses PIL library to open image in memory

        left = location['x']
        top = location['y']
        right = location['x'] + size['width']
        bottom = location['y'] + size['height']

        im = im.crop((left, top, right, bottom))  # defines crop points
        im.save(path)  # saves new cropped image

    def __update_category(self):
        self.__update_category_tvway()
        self.__update_category_world_cam()

    def __update_category_tvway(self):
        self.wdriver.get(self.__url_tvway)
        elements = self.wdriver.find_elements_by_css_selector('#page > div.sidebar-left > div:nth-child(1) > ul > li > a')
        list_category_and_url = []
        for t in elements:
            list_category_and_url.append((t.text, t.get_attribute('href')))

        # Уберем города и прочие ненужные ссылки
        list_category_and_url = list_category_and_url[7::]
        list_category_and_url = list_category_and_url[: -27 or None]

        # сохраним категории со ссылками
        for u in list_category_and_url:
            self.__add_to_list(u[0], u[1])

    def __update_category_world_cam(self):
        self.wdriver.get(self.__url_world_cam)
        self.wdriver.find_element_by_class_name('f_buttons').find_element_by_link_text('По категориям').click()
        tt = self.wdriver.find_element_by_id('category').find_elements_by_class_name('item')
        for t in tt:
            self.__add_to_list(t.text, t.get_attribute('href'))

    def print_on_values(self, values):
        values = values.split(',')

        # удалим лишние пробелы в начале и конце
        for i in range(len(values)):
            word = values[i]
            j = word
            if word[0] == ' ':
                j = word[1::]
            if word[-1] == ' ':
                j = word[:len(word) - 1]
            values[i] = j.lower()

        for request in values:
            self.__print_on_value(request)

    def __get_element_with_video_worlf_cam(self):
        # будем искать элемент, где можно включить видео
        element = None
        elements = self.wdriver.find_elements_by_css_selector('#one_cam > div.cam_image_services > noindex > iframe')
        if len(elements) != 0:
            return elements[0]

        return element

    def __get_element_with_video_tvway(self):
        # будем искать элемент, где можно включить видео
        element = None
        elements = self.wdriver.find_elements_by_css_selector('#page > div.body-area > iframe')
        if len(elements) != 0:
            return elements[0]

        return element

    def __download_from_world_cam(self, url, number_photo, path):
        self.wdriver.get(url)

        element = self.__get_element_with_video_worlf_cam()
        if element is None:
            print(f'Не могу найти, откуда скачивать видео с {url}.')
            exit(1)

        # прогрузка страницы
        time.sleep(2)

        # активируем видео
        element.click()

        # ждем, пока оно прогрузится
        time.sleep(7)

        # делаем необходимое количесвто снимков
        number_download = 0
        try:
            while number_download < number_photo:
                self.__take_screenshot(element, path=path + str(number_download + 1) + '.png')
                number_download += 1
                time.sleep(1)
        except Exception as e:
            print(e)

    def __download_from_tvway(self, url, number_photo, path):
        self.wdriver.get(url)

        element = self.__get_element_with_video_tvway()
        if element is None:
            print(f'Не могу найти, откуда скачивать видео с {url}.')
            exit(1)

        # прогрузка страницы
        time.sleep(2)

        # активируем видео
        element.click()

        # ждем, пока оно прогрузится
        time.sleep(7)

        # делаем необходимое количесвто снимков
        number_download = 0
        try:
            while number_download < number_photo:
                self.__take_screenshot(element, path=path + str(number_download + 1) + '.png')
                number_download += 1
                time.sleep(1)
        except Exception as e:
            print(e)

    def download_from_base(self, url, number_photo, path):
        if self.__url_world_cam in url:
            self.__download_from_world_cam(url, number_photo, path)
        if self.__url_tvway in url:
            self.__download_from_tvway(url, number_photo, path)


def main():
    print('Происходит сбор данных с сайтов. \n'
          'Пожалуйста, подождите. \n')

    # Попробуем создать объект класса
    dw = None
    try:
        dw = DownloadWebsite()
    except Exception as e:
        print(e)
        exit(1)

    #####################################################################################
    # print('На данный момент есть такие категории:')
    # dw.print_category()
    #####################################################################################

    #####################################################################################
    # print("Введите назваание категории, ссылки на которые хотите получить.")
    # print("Если хотите ввести несколько названий, то укажите их через запятую.\n")
    # values = input()
    # values = 'Море, строительные площадки, пляж'

    # выведем ссылки на заданные категории
    # dw.print_on_values(values)
    #####################################################################################

    #####################################################################################
    # скачаем видео с камеры
    url_world_cam = 'https://world-cam.ru/cams/web-camera-pitsunda-online/pension-musser-pitsunda-masterskoy-reserve-web-cameras-online/'
    url_tvway = 'http://tvway.ru/index.php?file=10457'
    path_download = os.getcwd() + '/download_webcam/'
    number_photo = 10
    dw.download_from_base(url_tvway, number_photo, path=path_download)
    #####################################################################################


if __name__ == '__main__':
    main()
