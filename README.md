# ltabs
Боковая панель рабочего стола с поддержкой расширений (QT) для GNU/Linux.

##### Лицензия:
Программа распространяется под лицензией GPLv3
В программе используются иконки Mono Dark Flattr:
https://github.com/hai-nguyen-van/mono-dark-flattr-icons
Распространяемых под лицензией CC BY-SA 4.0
Ссылка на лицензию https://raw.githubusercontent.com/hai-nguyen-van/mono-dark-flattr-icons/master/LICENSE
В некоторые иконки внесены изменения с целью адаптации к приложению.

##### Подготовка к сборке:
Установить библиотеку KWindowSystem:
```
# apt install libkf5windowsystem-dev
```
В QT Creator для сборочного комплекта выбрать системный профиль QT (qmake). В Ubuntu 18.04 размещён по пути `/usr/lib/qt5/bin/qmake`
Сборка выполняется стандартыми средствами QT Creator.
