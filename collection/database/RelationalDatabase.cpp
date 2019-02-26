
#include "RelationalDatabase.h"
#include <cstdint>
#include <cstdio>
#include "sqlite3/sqlite3.h"

RelationalDatabase::RelationalDatabase(sqlite3** sql) : db(*sql) {}

RelationalDatabase::~RelationalDatabase() {
  sqlite3_close(db);
  delete db;
}

std::optional<RelationalDatabase> RelationalDatabase::loadDatabase(
    const std::string& dbName) {
  sqlite3* db;
  char* errMsg = nullptr;
  int32_t res = sqlite3_open(dbName.c_str(), &db);

  if (res) {
    return std::optional<RelationalDatabase>(&db);
  }
  sqlite3_close(db);
  return std::nullopt;
}