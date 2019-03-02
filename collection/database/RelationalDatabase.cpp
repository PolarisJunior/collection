
#include "RelationalDatabase.h"
#include <cstdint>
#include <cstdio>
#include "sqlite3/sqlite3.h"

RelationalDatabase::RelationalDatabase(sqlite3** sql) : db(*sql) {}

RelationalDatabase::~RelationalDatabase() {
  sqlite3_close(db);
}

std::optional<RelationalDatabase> RelationalDatabase::loadDatabase(
    const std::string& dbName) {
  sqlite3* db;

  int32_t res = sqlite3_open(dbName.c_str(), &db);

  if (!res) {
    return std::optional<RelationalDatabase>(&db);
  }

  sqlite3_close(db);
  return std::nullopt;
}

bool RelationalDatabase::createTable() {
  int32_t r;
  char* errMsg;
  std::string query =
      "CREATE TABLE Accounts(id INT PRIMARY KEY, name TEXT, password TEXT);";
  r = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);

  if (r != SQLITE_OK) {
    return false;
  } else {
    return true;
  }
}

bool RelationalDatabase::exec() {
  return false;
}