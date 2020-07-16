package controllers

import (
	"net/http"
	"strconv"

	"github.com/gorilla/mux"
)

// VarsUint parse uint
func VarsUint(v string, r *http.Request) (uint64, error) {
	vars := mux.Vars(r)
	uid, err := strconv.ParseUint(vars[v], 10, 32)
	return uid, err
}
