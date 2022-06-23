# scan-util-test-kaspersky

Требуется реализовать утилиту на языке C++, работающую из командной строки, выполняющую сканирование файлов в директории, с целью нахождение в ней “подозрительных” (suspicious) файлов.


В рамках задачи определено 3 типа “подозрительного” содержимого в файле:

JS suspicious: файл с расширением .js, содержащий строку: <script>evil_script()</script>
CMD suspicious: файл с расширением CMD/BAT, содержащий строку: rd /s /q "c:\windows"
EXE suspicious: файл с расширением EXE/DLL, содержащий строки: CreateRemoteThread, CreateProcess
После завершения выполнения утилиты пользователю должен быть выведен отчет о сканировании, в котором присутствует следующая информация:

общее количество обработанных файлов;
количество детектов на каждый тип “подозрительного” содержимого;
количество ошибок анализа файлов (например, не хватает прав на чтение файла);
время выполнения утилиты.
Пример исполнения утилиты из командной строки:

>scan_util C:\Users\user\Downloads

```
====== Scan result ======

Processed files: 150

JS detects: 5

CMD detects: 1

EXE detects: 2

Errors: 1

Execution time: 00:00:31 

=========================
```

Для упрощения задачи условимся:

В директории находятся только файлы, вложенных директорий нет;
В каждом файле присутствует только один тип  “подозрительного” содержимого.
Рекомендуется максимальное использования (утилизация) вычислительных ресурсов устройства, на котором выполняется утилита.