import os
import time
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import urllib.request
import threading


def _download(url, path, name):
    try:
        urllib.request.urlretrieve(url, path + '/' + name + '.jpg')
    except Exception as e:
        print('Ошибка: ', e, 'Не удалось скачать: ', url, '\n', end='')


def download_jpg(url, name, path=os.getcwd()):
    thread = threading.Thread(target=_download, args=[url, path, name])
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


def download_image_from_yandex(value, number_pictures, min_resolution, driver_path, path=os.getcwd()):
    wdriver = webdriver.Chrome(executable_path=driver_path)

    # откроем сайт
    wdriver.get('https://yandex.ru')

    # введем запрос
    element_search = wdriver.find_element_by_class_name('input__control')
    element_search.send_keys(value, Keys.ENTER)

    # откроем страницу с картинками
    url_pictures = wdriver.find_element_by_link_text('Картинки').get_attribute('href')
    wdriver.get(url_pictures)

    # откроем первую картинку
    url_first_picture = wdriver.find_element_by_class_name('serp-item__link').get_attribute('href')
    wdriver.get(url_first_picture)

    # счетчик скаченных картинок
    now_download_pictures = 1
    while now_download_pictures <= number_pictures:

        # получим url основной картинки
        url_main_photo = wdriver.find_element_by_class_name('MMImage-Origin').get_attribute('src')

        # скачаем основоное фото
        download_jpg(url_main_photo, str(now_download_pictures), path)
        now_download_pictures += 1

        # откроем список с разрешениями картинок и загрузим его (если он есть!)
        button = wdriver.find_elements_by_class_name('MMViewerButtons-ImageSizes')
        if len(button) != 0:
            button[0].click()
            list_resolutions = wdriver.find_elements_by_class_name('MMViewerButtons-ImageSizesListItem')

            # если картинки подходят, то скачаиваем их
            for photo in list_resolutions:
                if photo.text != '':
                    if right_resolution(min_resolution=min_resolution, now_resolution=photo.text):
                        download_jpg(photo.get_attribute('href'), str(now_download_pictures), path)

                        # увеличим счетчик
                        now_download_pictures += 1

        # откуроем следующую картинку
        wdriver.find_element_by_class_name('MediaViewer_theme_fiji-ButtonNext').click()


def main():
    value = "fire"
    number_pictures = 40
    min_resolution = "800×600"
    driver_path = os.getcwd() + '/chromedriver'
    path_save = os.getcwd() + '/download_photo_yandex'
    download_image_from_yandex(value, number_pictures, min_resolution, driver_path, path_save)


if __name__ == '__main__':
    main()
