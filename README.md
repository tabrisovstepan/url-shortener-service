## Проект url-shortener-service
Простой HTTP сервис для сокращения URL наподобие Bitly и ему подобных сервисов.

## Stack
Используемые технологии:
- C++17
- Boost.beast
- Boost.program_options
- Boost.json
- SQLite3

## Dependencies
- SQLite3
- Boost 1.81.0
- CMake 3.20

## Database structure

### `urls`

| Колонка | Тип | Комментарий |
| --- | --- | --- |
| id | int | Айди записи, автоинкремент, первичный ключ |
| base_url | text | Полное представление URL |
| short_url | text | Короткое представление URL |

## REST API
Методы REST API реализуют [CRUD](https://en.wikipedia.org/wiki/Create,_read,_update_and_delete) интерфейс над базой данных - позволяют создавать (C - craete), читать (R - read). В целях упрощения, опустим обновление(U - update) и удаление (D - delete).
### POST `/url` 
Создать короткое URL представление.
Данные передаются в теле запроса в формате JSON. Пример тела запроса:
```
{
	"target_url":"https://github.com/tabrisovstepan/url-shortener-service"
}
```
Ответ в формате JSON. Пример:
```
{
	"id": "0",
	"long_url": "https://github.com/tabrisovstepan/url-shortener-service",
	"short_url": "http://localhost:8989/253437254"
}
```

HTTP коды ответов:
- Успех - 201
-  Отсутствует поле формы - 400
- Короткое представление для данного URL уже существует - 409 
- Ошибка сервера (БД недоступна) - 500

### GET `/{short-url}` 
Получить перенаправление по созданному короткому URL представлению.

Ответ: Перенаправление по оригинальному URL.

HTTP коды ответов:
- Успех - 301
- {short-url} отсутствует в адресе - 400
- Ошибка сервера (БД недоступна) - 500



### POST `/url/custom`

Создать короткое URL представление.
Данные передаются в теле запроса в формате JSON.  Пример тела запроса:
```
{
	"target_url":  "https://github.com/tabrisovstepan/url-shortener-service",
	"short_url":  "http://localhost:8989/tast-task"
}
```
Ответ в формате JSON:
```
{
	"id": "0",
	"long_url": "https://github.com/tabrisovstepan/url-shortener-service",
	"short_url": "http://localhost:8989/tast-task"
}
```

## Installation
Клонируйте репозиторий:
```sh
git clone https://github.com/tabrisovstepan/url-shortener-service
cd url-shortener-service
``` 
Соберите проект:
```sh
cmake -B build
cmake --build build --target install
```
Установленный бинарный файл находится в `/usr/local/bin`
Пример запуска:
```sh
/usr/local/bin/url-shortener-service --help
```
```
