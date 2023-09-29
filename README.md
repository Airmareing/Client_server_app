# Client_server_app
- В корневой папке репозитория находятся: 
    - исходные файлы клиент-серверного приложения,
    - Makefile.
- В папке "final/" находятся:
    - Бинарный файл собранной системы,
    - Patch-файл,
    - в папке "config/" лежат все дополненные мною для интеграции приложения файлы исходной системы,
    - в папке "src/" Makefile и исходный файл приложения, которые находились в папке /user/test1/ для интеграции в систему.
Исполнительный файл под названием test1 (все файлы в системе, связанные с клиент-серверным приложением, используют это имя) был успешно собран в директорию bin/ и добавлен в автозапуск системы (символическая ссылка в директории /etc/init.d/ и сам скрипт в /etc/rc.d)
----
- Для запуска проекта необходимо выполнить:
```
sudo make
```
Демонстрация работы:
![example](example.png)