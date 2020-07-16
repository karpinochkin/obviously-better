package database

import "testing"

func TestConnect(t *testing.T) {
	_, err := Connect()
	if err != nil {
		t.Fatalf("database connect error : %v", err)
	}
}
