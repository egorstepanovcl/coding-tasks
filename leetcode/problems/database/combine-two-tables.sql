-- Решил: Егор Степанов <https://github.com/egorstepanovcl>

-- Название: 175. Объединить две таблицы (175. Combine Two Tables)

-- Задача:
-- Таблица: Person
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | personId    | int     |
-- | lastName    | varchar |
-- | firstName   | varchar |
-- +-------------+---------+
-- personId является первичным ключом (столбец с уникальными значениями) для этой таблицы.
-- Эта таблица содержит информацию об идентификаторе некоторых лиц и их именах и фамилиях.

-- Таблица: Address
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | addressId   | int     |
-- | personId    | int     |
-- | city        | varchar |
-- | state       | varchar |
-- +-------------+---------+
-- addressId является первичным ключом (столбец с уникальными значениями) для этой таблицы.
-- Каждая строка этой таблицы содержит информацию о городе и штате одного человека с ID = PersonId.

-- Напишите решение, которое будет сообщать имя, фамилию, город и штат каждого человека в таблице Person. Если адрес personId отсутствует в таблице Address, вместо него выведите null.
-- Верните таблицу результатов в любом порядке.
-- Формат результата приведен в следующем примере.

-- Пример 1:
-- Вход:
-- Person table:
-- +----------+----------+-----------+
-- | personId | lastName | firstName |
-- +----------+----------+-----------+
-- | 1        | Wang     | Allen     |
-- | 2        | Alice    | Bob       |
-- +----------+----------+-----------+
-- Address table:
-- +-----------+----------+---------------+------------+
-- | addressId | personId | city          | state      |
-- +-----------+----------+---------------+------------+
-- | 1         | 2        | New York City | New York   |
-- | 2         | 3        | Leetcode      | California |
-- +-----------+----------+---------------+------------+
-- Выход: 
-- +-----------+----------+---------------+----------+
-- | firstName | lastName | city          | state    |
-- +-----------+----------+---------------+----------+
-- | Allen     | Wang     | Null          | Null     |
-- | Bob       | Alice    | New York City | New York |
-- +-----------+----------+---------------+----------+
-- Объяснение: 
-- В адресной таблице нет адреса для personId = 1, поэтому мы возвращаем null для его города и штата.
-- АдресId = 1 содержит информацию об адресе personId = 2.

SELECT 
    p.firstName,
    p.lastName,
    a.city,
    a.state
FROM 
    Person p
LEFT JOIN 
    Address a
ON 
    p.personId = a.personId;