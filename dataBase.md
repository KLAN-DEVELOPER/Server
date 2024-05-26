# Операций с таблицами
* Термины



# Термины 

Имеются следующие возможности по работе с таблицей `termins`:
 * Добавить термин `setTermin`.
 * Добавить парадигму к термину `setTerminParadigm`.
 * Получить парадигму термина.

## setTermin
Добавляет новый термин в указанный словарь. Если термин уже существует в таблице, то операция добавления игнорируется

P.S. Сейчас по умолчанию все термины добавляются в словарь админа!!!


### Параметры процедуры
* mainForm - нормальная форма термина.
* stemma - основна термина.
* morphParameters - морфологические признаки термина.
* speechPart - часть речи, к которой принадлежит термин.   

Параметры соответсвуют аргументам процедуры по порядку.

 ```sql
create function setTermin(varchar(50), varchar(50), varchar(50), varchar(50)) returns void
as $$
	INSERT INTO termins (vocabularyId, mainForm, stemma, morphParameters, speechPart)
    VALUES (1, $1, $2, $3, $4)
    ON CONFLICT (mainForm) DO NOTHING
$$ language sql;
 ```

### Использование
```sql
    select setTermin('быть', 'быть', 'Вид: нс, Переходность: нп', 'Глаг');
```



## setTerminParadigm
Добавляет парадигму к термину, по его идентификатору.

### Параметры процедуры
* идентификатор термина в таблице `termins`, к которому нужно добавить парадигму.
* ending - окончание термина.
* properties - какие-то своства окончания 
(Тут пока не понятно, что это за данные и как они будут использоваться)


```sql
create function setTerminParadigm(integer, varchar(50), varchar(50)) returns void
as $$
	INSERT INTO paradigms (ending, properties, terminId)
    VALUES ($2, $3, $1)
$$ language sql;
```

### Использование
Допустим, что добавили термин `быть` в таблицу терминов. Для добавления парадигмы нужно сделать вызов:

```sql
select setTerminParadigm(4, 'будем', 'ед;'); 
```

## Запрос на получение парадигмы термина
Данный запрос вернет только таблицу с данными парадигмы термина 
```sql
select paradigms.* from paradigms inner 
     join termins on termins.id = paradigms.terminId
     where termins.id=[идентификатор_термина]
```

Если необходимо получить объединеную таблицу терминов и искомой парадигмы, то выполните вот такой запрос:
```sql
select paradigms.* from paradigms inner 
     join termins on termins.id = paradigms.terminId
     where termins.id=[идентификатор_термина]
```