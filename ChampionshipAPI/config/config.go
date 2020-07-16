package config

import (
	"fmt"
	"log"
	"os"
	"strconv"

	"github.com/joho/godotenv"
)

var (
	PORT      = 0
	SECRETKEY []byte
	DBDRIVER  = ""
	DBNAME    = ""
)

// Load config
func Load() {
	var err error
	err = godotenv.Load()
	if err != nil {
		log.Fatal(err)
	}

	PORT, err = strconv.Atoi(os.Getenv("PORT"))
	if err != nil {
		PORT = 9999
	}

	DBDRIVER = os.Getenv("DB_DRIVER")
	DBNAME = fmt.Sprintf(
		"%s:%s@tcp(%s:%s)/%s?charset=utf8mb4&parseTime=True&loc=Local",
		os.Getenv("DB_USER"),
		os.Getenv("DB_PASSWORD"),
		os.Getenv("DB_HOST"),
		os.Getenv("DB_PORT"),
		os.Getenv("DB_NAME"),
	)

	SECRETKEY = []byte(os.Getenv("API_SECRET"))
}
