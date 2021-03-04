import os
import urllib.request
import datetime
import threading
import time


class Downloader:
    def __init__(self, url, path=os.getcwd()):
        self._url = url
        self._path = path

    # url - то, откуда скачиваем
    # path - папка, куда скачаиваем (по умолчанию в рабочую директрию)
    def download_mp4(self, time_work=0):
        now = datetime.datetime.now()
        # имя файла будет в формате день_месяц_год_час_минута_секунда
        name = str(now.strftime("%d%m%Y_%H%M%S")) + '.mp4'

        thread = threading.Thread(target=self._download_file, args=[name])

        thread.daemon = True
        thread.start()
        # time.sleep(time_work)
        print('Загузка успешно завершена')

    def download_jpeg(self):
        now = datetime.datetime.now()
        # имя файла будет в формате день_месяц_год_час_минута_секунда
        name = str(now.strftime("%d%m%Y_%H%M%S")) + '.jpeg'
        thread = threading.Thread(target=self._download_file, args=[name])
        thread.start()

    def _download_file(self, name):
        urllib.request.urlretrieve(self._url, self._path + '/' + name)


def main():
    # камера из Адлера
    url = 'http://85.172.107.108:10033//axis-cgi/mjpg/video.cgi?videocodec=h264&date=1&clock=3&resolution=800x600' \
          '&streamprofile=quality '
    url1 = 'https://yastatic.net/video-player/0xe50564e2eb6/pages-common/ok/ok.html#html=%3Ciframe%20src%3D%22%2F%2Fok.ru%2Fvideoembed%2F1493597491696%3Fautoplay%3D1%26amp%3Bya%3D1%22%20frameborder%3D%220%22%20scrolling%3D%22no%22%20allowfullscreen%3D%221%22%20allow%3D%22autoplay%3B%20fullscreen%3B%20accelerometer%3B%20gyroscope%3B%20picture-in-picture%22%20aria-label%3D%22Video%22%3E%3C%2Fiframe%3E&counters=%7B%22reqid%22%3A%221595440388559345-547269378434271620800163-sas1-6869%22%2C%22duration%22%3A205%2C%22videoUrl%22%3A%22http%3A%2F%2Fok.ru%2Fvideo%2F1493597491696%22%2C%22heartbeats%22%3A%7B%22singlePath%22%3A%22heartbeat.single.fserp%22%2C%22repeatPath%22%3A%22heartbeat.repeat.fserp%22%7D%2C%22table%22%3A%22video_tech%22%7D'
    url2 = 'https://open.ivideon.com/embed/v2/?server=100-VMpwFEyHSAc7CQ8CVPHa36&camera=0&width=&height=&lang=ru'
    url_photo = 'https://img1.fonwall.ru/o/hq/poppy-red-sunset-clouds.jpeg'
    d = Downloader(url_photo)
    # сколько секунд будет скачиваться
    # time_work = 10
    d.download_jpeg()


if __name__ == '__main__':
    main()
