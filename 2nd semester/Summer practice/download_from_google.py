import os
import time
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options as ChromeOptions
import urllib.request
import threading


def down(url, path, name, expansion):
    try:
        urllib.request.urlretrieve(url, path + '/' + name + expansion)
    except Exception as e:
        print('Ошибка: ', e, 'Не удалось скачать: ', url, '\n', end='')


def download(url, name, path=os.getcwd()):
    all_expansion = ['jpeg', 'png', 'gif', 'tiff', 'webp', 'svg', 'eps', 'raw', 'psd', 'cdr', 'jpg']
    expansion = ''
    for exp in all_expansion:
        if exp in url.lower():
            expansion = exp
    if expansion == '':
        expansion = 'jpeg'
    thread = threading.Thread(target=down, args=[url, path, name, '.' + expansion])
    thread.start()
    time.sleep(1)


def cut(resolution):
    resolution_int = ['', '']
    flag = True
    for symbol in resolution:
        if symbol.isdigit() and flag:
            resolution_int[0] += symbol
        elif symbol.isdigit() and not flag:
            resolution_int[1] += symbol
        else:
            flag = False
    return resolution_int


def right_resolution(min_resolution, now_resolution):
    # получим разрешение min_resolution в числовом формате
    min_resolution_int = cut(min_resolution)

    now_resolution_int = cut(now_resolution)
    return int(now_resolution_int[0]) >= int(min_resolution_int[0]) and int(now_resolution_int[1]) >= int(
        min_resolution_int[1])


def download_image_from_google(value, number_pictures, min_resolution, driver_path, path=os.getcwd()):
    options = ChromeOptions()
    # options.add_argument("--headless")

    wdriver = webdriver.Chrome(executable_path=driver_path, options=options)

    # откроем сайт
    wdriver.get('https://google.com')

    # введем запрос
    element_search = wdriver.find_element_by_class_name('gLFyf')
    element_search.send_keys(value, Keys.ENTER)

    # откроем страницу с картинками
    url_pictures = wdriver.find_element_by_link_text('Картинки').get_attribute('href')
    wdriver.get(url_pictures)

    # кликнем на первое изображение
    wdriver.find_element_by_class_name('islib').click()

    now_download_pictures = 0
    name_photo = 0
    while now_download_pictures <= number_pictures:
        # получим разрешение
        now_resolution = wdriver.find_element_by_css_selector('#Sva75c > div > div > div.pxAole > div.tvh9oe.BIB1wf > '
                                                              'c-wiz > div.OUZ5W > div.zjoqD > div > div.v4dQwb > a > '
                                                              'span')
        # сделаем строчку с разрешением видимой, чтобы получить поле text
        wdriver.execute_script("arguments[0].style.display = 'block';", now_resolution)
        now_resolution = now_resolution.text

        # если фотка подходит по разрешению
        if now_resolution != '':
            if right_resolution(now_resolution=now_resolution, min_resolution=min_resolution):

                url_img = wdriver.find_element_by_css_selector('#Sva75c > div > div > div.pxAole > div.tvh9oe.BIB1wf > '
                                                               'c-wiz > div.OUZ5W > div.zjoqD > div > ''div.v4dQwb > '
                                                               'a > img').get_attribute('src')

                # если время загрузки картинки будет превышено, то установим флаг
                all_time_wait = 0
                is_good_url = True
                # Подождем, пока прогрузится картинка
                while ('http' not in url_img) or ('https://encrypted' in url_img):
                    time.sleep(0.1)
                    url_img = wdriver.find_element_by_css_selector(
                        '#Sva75c > div > div > div.pxAole > div.tvh9oe.BIB1wf > c-wiz > div.OUZ5W > div.zjoqD > div > '
                        'div.v4dQwb > a > img').get_attribute('src')
                    all_time_wait += 0.1

                    if all_time_wait > 10:
                        is_good_url = False
                        break

                if is_good_url:
                    # print(url_img)
                    download(url_img, str(name_photo), os.getcwd() + '/download_from_google/')
                    now_download_pictures += 1
                    name_photo += 1

        # нажмём на кнопочку вперёд
        button_next = wdriver.find_element_by_css_selector('#Sva75c > div > div > div.pxAole > div.tvh9oe.BIB1wf > '
                                                           'c-wiz > div.OUZ5W > div.zjoqD > div > div.ZGGHx > a.gvi3cf')
        wdriver.execute_script("arguments[0].style.display = 'block';", button_next)
        button_next.click()

        # # если картинки кончились
        if wdriver.find_element_by_class_name('OuJzKb').text == 'Больше ничего нет':
            print('Картинки кончились')


def main():
    value = "fire"
    number_pictures = 100
    min_resolution = "800×600"
    chrome_driver_path = os.getcwd() + '/chromedriver'
    path_save = os.getcwd() + '/download_from_google'
    download_image_from_google(value, number_pictures, min_resolution, chrome_driver_path, path_save)
    print("Скачивание завершено")


if __name__ == '__main__':
    main()
