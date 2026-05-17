# Сборка и запуск

Проект собирается через `Makefile`.

- объектные файлы складываются в `build/`
- итоговый исполняемый файл создаётся в корне как `./app`
- скрипты лежат в папке `scripts/`

## Быстрая сборка

```bash
./scripts/build.sh
```

## Сборка и запуск одной командой

```bash
./scripts/run.sh
```

## Требования

- Linux / WSL
- `g++`
- `make`
- `gnuplot` для показа графиков и сохранения `jpeg`

## Примеры запуска

### HW_2: декодирование символов из шрифта

```bash
./scripts/run.sh --font=B --fill=o --background=.
./scripts/run.sh --font=K --fill=* --background=_
./scripts/run.sh --font=9 --fill=0 --background=.
./scripts/run.sh --font=A --fill=# --background=' '
```

### HW_2: постоянное напряжение `constV`

```bash
./scripts/run.sh -R1=100k -R2=1k -C1=100u --signal=constV
./scripts/run.sh -R1=100k -R2=1k -C1=100u --signal=constV -E1=12
./scripts/run.sh -R1=47k -R2=10k -C1=220u --signal=constV -E1=5 --step=0.01 -T=1
./scripts/run.sh -R1=10k -R2=100k -C1=47u --signal=constV --charge=true --discharge=false
./scripts/run.sh -R1=10k -R2=100k -C1=47u --signal=constV --charge=false --discharge=true
./scripts/run.sh -R1=100k -R2=1k -C1=100u --signal=constV --jpeg=const_signal.jpeg
```

### HW_2: переменные сигналы

```bash
./scripts/run.sh -R1=100k -R2=200k -C1=100u --signal=sin
./scripts/run.sh -R1=100k -R2=200k -C1=100u --signal=sin -E1=15 --step=0.05 --jpeg=sin_signal.jpeg
./scripts/run.sh -R1=33k -R2=120k -C1=68u --signal=triangle -E1=8 -T=12
./scripts/run.sh -R1=33k -R2=120k -C1=68u --signal=sawtooth -E1=8 -T=12 --jpeg=saw.jpeg
./scripts/run.sh -R1=22k -R2=220k -C1=10u --signal=meandr -E1=10 --step=0.02
./scripts/run.sh -R1=22k -R2=220k -C1=10u --signal=halfSin -E1=10 -T=9.42
./scripts/run.sh -R1=22k -R2=220k -C1=10u --signal=rectSin -E1=10 -T=9.42 --jpeg=rectsin.jpeg
```

### HW_2: допустимые единицы измерения в параметрах

```bash
-R1=100k
-R2=1M
-C1=100u
-T=8
```

Поддерживаются суффиксы:

- `p` - pico
- `n` - nano
- `u` - micro
- `k` - kilo
- `M` - mega
- `G` - giga

# Задачи

> [!important]
> Папка с заданиями : https://disk.yandex.ru/i/1rWm6euojHyyYA

- [SW_1](SW/SW_1.md) (2026.02.24) или [pdf](https://disk.yandex.ru/d/vh5SiIpPKaiskQ)

# Лекции

## 2026.02.10

1. пример составления алгоритмов (на примере поиска максимума)
2. компьютер выполняет 4ре операции!!!
3. понятие локальной/глобальной переменной
4. объявление переменных и функций
5. объявление массива и обращение к элементам массива
6. цикл for(н.у.; условие выхода из цикла; действие) {}
7. условие ветвления if(условие) {выполняется если верно}

## 2026.02.17

1. цикл while(...)
2. аргументы функции main()
3. С-строки
4. добили сортировку выбором

## 2026.02.24

1. многофайловый проект
	1.1. содержание заголовочных файлов
	1.2. компиляция многофалового проекта ![[make.sh]]
2. ключи компиляции
	2.1. -g
	2.2. -o
	2.3. -std=c++17
3. сортировка выбором с ключом isAsc <- добиваем сортировку выбором
4. разбиение программы на файлы
5. отладка с помощью gdb
6. начало тестирования
7. тернарный оператор

# основные команды GIT

- git status
- git add .
- git commit -m "..."
- git log
- git log --oneline
- git log --oneline --graph --all --decorate
- git log --stat --graph --oneline --all --decorate
- git remote add origin \[ssh link\]
- git push -u origin master
- git pull origin
- git clone \[ssh link\] //if publit you may use https
- git tag \[name of tag\]
- git push -u origin --tags //отправить все метки на удалённый репозиторий
- git checkout 
- git branch
- git config --global user.name //user.email
- git rm --cached [file] <- удалить из отслеживаемых, если не успели сделать commit

## создание своей команды git (создание alias)

- git config --global alias.logs "log --oneline --graph --all --decorate"
- git config --global alias.lgst "log --stat --graph --oneline --all --decorate"

# основные команыд gdb

- break [имя функции]
- break [номер строчки]
- break [имя файла:имя строчки]
- info break
- delete break
- run - запуск программы на отладку
- continue - продолжить выполнение программы до точки останова
- step - войти в функцию
- next - выполнить операцию не входя в функцию
- p *\[имя массива\]@\[число элементов в массиве\]
- p \[имя переменной\]
- p/x [...]

# литература

0. Эккель Б. Философия С++. Введение в стандартные С++. - СПб.: Питер, 2004. - 572 с.
1. Эккель Б., Эллисон Ч. Филосовия С++. Практическое программирование. - СПб.: Питер, 2004. - 608 с.
2. Лафоре Р. Объектно-ориентированное программирование в C++ - СПб.: Питер, 2004. - 923 с.
3. Седжевик Роберт Фундаментальные алгоритмы на С++. Анализ/структуры данных/сортировка/поиск. - К.: Издательство "ДиаСофт", 2001. - 688с
4. Седжевик Роберт Фундаментальные алгоритмы на С++. Алгоритмы на графах. - СПб: ООО "ДиаСофтЮП", 2002. - 496с
5. Страуструп Б. Язык программирования C++ - М. : Бином, 2011. - 1135 с.
6. Якушев Д. М. "Философия" программирования на языке С++ - М. : Новый издательский дом, 2004. - 319 с.
7. Марченко А. Л. С++. Бархатный путь - М. : Горячая линия-Телеком, 2001. - 399 с. 396.
8. Шилдт Г. Справочник программиста по С/С++ - М. : Вильямс, 2000. - 447 с.
9. Фленов М. Е. Программирование на С++ глазами хакера - СПб. : БХВ-Петербург, 2005. - 330 с.
10. Кормен Т., Лейзерсон Ч., Ривест Р. Алгоритмы : построение и анализ: Пер - М. : МЦНМО, 1999. - 955 с.
11. и другие понятные книги...
12. Поляков К.Ю. Программирование. Python. C++. Часть 1, 2, 3, 4. -М.: Бином. Лаборатория знаний, 2019. - xxx
13. Лав. Р. Linux. Системное программирование. - СПб.: Питер, 2008. - 416с.


# Интернет

1. https://ru.cppreference.com/
2. https://habr.com




