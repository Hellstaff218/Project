#!/bin/bash

# Проверка что это git репозиторий
if [ ! -d ".git" ]; then
    echo "Текущая папка не является git репозиторием."
    exit 1
fi

echo "Введите сообщение коммита:"
read commitMessage

if [ -z "$commitMessage" ]; then
    echo "Сообщение коммита не может быть пустым."
    exit 1
fi

echo "Введите тег (например SW_1_1):"
read tagName

if [ -z "$tagName" ]; then
    echo "Тег не может быть пустым."
    exit 1
fi

echo
echo "Добавление файлов..."
git add .

echo
echo "Создание коммита..."
git commit -m "$commitMessage"

echo
echo "Создание тега..."
git tag "$tagName"

echo
echo "Коммит и тег созданы."

echo
read -p "Отправить изменения на сервер? (y/n): " pushChoice

if [ "$pushChoice" = "y" ]; then
    git push
    git push --tags
fi

echo "Готово."