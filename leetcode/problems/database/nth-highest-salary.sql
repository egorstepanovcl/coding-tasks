-- Решил: Егор Степанов <https://github.com/egorstepanovcl>

-- Название: 177. Самая высокая зарплата (177. Nth Highest Salary)

-- Задача:
-- Таблица: Employee
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | id          | int  |
-- | salary      | int  |
-- +-------------+------+
-- id это первичный ключ (столбец с уникальными значениями) для данной таблицы.
-- Каждая строка этой таблицы содержит информацию о зарплате сотрудника.
 
-- Напишите решение для поиска nᵗʰ наибольшей зарплаты из таблицы Employee. Если не найдено nᵗʰ наибольших зарплат, верните null.
-- Формат результата приведен в следующем примере.

-- Пример 1:
-- Вход: 
-- Employee таблица:
-- +----+--------+
-- | id | salary |
-- +----+--------+
-- | 1  | 100    |
-- | 2  | 200    |
-- | 3  | 300    |
-- +----+--------+
-- n = 2
-- Выход: 
-- +------------------------+
-- | getNthHighestSalary(2) |
-- +------------------------+
-- | 200                    |
-- +------------------------+

-- Пример 2:
-- Вход: 
-- Employee таблица:
-- +----+--------+
-- | id | salary |
-- +----+--------+
-- | 1  | 100    |
-- +----+--------+
-- n = 2
-- Выход: 
-- +------------------------+
-- | getNthHighestSalary(2) |
-- +------------------------+
-- | null                   |
-- +------------------------+

CREATE OR REPLACE FUNCTION NthHighestSalary(N INT) 
RETURNS TABLE (Salary INT) 
AS $$
BEGIN
  IF N < 1 THEN
    RETURN QUERY 
    SELECT CAST(NULL AS INT);
  ELSE
    RETURN QUERY (
      SELECT DISTINCT e.salary
      FROM Employee e
      ORDER BY e.salary DESC
      LIMIT 1 OFFSET N-1
    );
  END IF;
END;
$$ LANGUAGE plpgsql;