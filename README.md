# MessageTypeProject

Проект демонстрирует реализацию типа данных `MessageType`, предназначенного для обмена сообщениями между клиентом и сервером через API.  
Реализована сериализация и десериализация без сторонних библиотек, с поддержкой операторов потокового ввода/вывода и модульных тестов на **GoogleTest**.

- Поддерживаемые типы сообщений:
  - `System`
  - `Server`
  - `Session`
- Конвертация:
  - `ToString(MessageType)` → `"system"`, `"server"`, `"session"`
  - `FromString("system", type)` → `MessageType::System`
- Сериализация / десериализация (inline-обёртки)
- Потоковые операторы `<<` и `>>`
- Модульные тесты на **GoogleTest**
- Пример консольного приложения (`mainApp`)

**Основные функции**

`Convert to string`

[[nodiscard]] constexpr std::string ToString(MessageType type) noexcept;

`Convert from string (with validation)`

[[nodiscard]] bool FromString(std::string_view text, MessageType& out) noexcept;

`Serialization synonyms`

[[nodiscard]] std::string Serialize(MessageType type) noexcept;
[[nodiscard]] bool Deserialize(std::string_view text, MessageType& out) noexcept;

`Stream operators`

std::ostream& operator<<(std::ostream& os, MessageType type);
std::istream& operator>>(std::istream& is, MessageType& type);

**Как собрать**

_Создание директории сборки_

mkdir build && cd build

_Конфигурация CMake_

cmake ..

_Сборка_

cmake --build .

**Тестирование**

cd build
ctest --verbose

**Требования**

- Компилятор: C++20 (GCC 10+, Clang 10+)
- CMake: 3.16+
- Библиотеки: GoogleTest (автоматически загружается)
