
#pragma once
#include <memory>
#include <optional>
#include <string>

struct sqlite3;

class RelationalDatabase {
 public:
  static std::optional<RelationalDatabase> loadDatabase(
      const std::string& dbName);

  ~RelationalDatabase();
  RelationalDatabase(sqlite3** sql);

 private:
  sqlite3* db;
  bool valid;
};