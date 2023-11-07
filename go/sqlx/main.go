package main

import (
	"database/sql"
	"fmt"

	"github.com/jmoiron/sqlx"
	_ "github.com/mattn/go-sqlite3"
)

var db *sql.DB

func main() {
	db, err := sqlx.Open("sqlite3", "db.db")
	if err != nil {
		panic(err)
	}

	err = db.Ping()
	if err != nil {
		panic(err)
	}

	// Exec
	// schema := `CREATE TABLE IF NOT EXISTS place (
	// 	country text,
	// 	city text NULL,
	// 	telcode integer
	// );`

	// result, err := db.Exec(schema)
	// if err != nil {
	// 	panic(err)
	// }

	// fmt.Printf("result from exec(schema): %+v\n", result)

	cityState := `INSERT INTO place (country, telcode) VALUES (?, ?)`
	countryCity := `INSERT INTO place (country, city, telcode) values (?, ?, ?)`

	db.MustExec(cityState, "Hong kong", 852)
	// fmt.Printf("1 result: %+v", result)
	db.MustExec(cityState, "singapore", 52)
	// fmt.Printf("2 result: %+v", result)
	db.MustExec(countryCity, "south africa", "johannesburg", 10)
	// fmt.Printf("3 result: %+v", result)

	selectAll := `select * from place where telcode = ? LIMIT 1;`
	// same as -> select 'country', ...
	// rows, err := db.Query("select ?, telcode from place;", "contry")
	rows, err := db.Queryx(selectAll, 52)
	if err != nil {
		panic(err)
	}

	type Place struct {
		Country       string
		City          sql.NullString
		Telephonecode int `db:"telcode"`
	}

	p1 := Place{}
	for rows.Next() {
		// err = rows.Scan(&p1) thats not possible with normal scan
		// you have to do something like:
		// p := reflect.ValueOf(&p1).Elem()

		// numCols := p.NumField()
		// columns := make([]interface{}, numCols)
		// for i := 0; i < numCols; i++ {
		// 	field := p.Field(i)
		// 	columns[i] = field.Addr().Interface()
		// }

		// err := rows.Scan(columns...)
		///////

		err := rows.StructScan(&p1)
		if err != nil {
			fmt.Println(err)
		}

		fmt.Printf("%+v\n", p1)
	}

	p2 := Place{}
	row := db.QueryRowx("SELECT * FROM place WHERE telcode=?", 852)
	row.StructScan(&p2)
	fmt.Printf("row: %+v\n", p2)

	p3 := Place{}
	ps := []Place{}

	err = db.Get(&p3, selectAll, 52)
	if err != nil {
		panic(err)
	}

	err = db.Select(&ps, "SELECT * FROM place WHERE telcode > ?", 50)
	if err != nil {
		panic(err)
	}

	fmt.Printf("ps: %v\n", ps)
	fmt.Printf("p3: %v\n", p3)

	// p4 := Place{Country: "Hong kong"}
	// rows, err = db.NamedQuery(`SELECT * FROM place WHERE country=:country`, p4)
}
