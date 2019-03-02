
#pragma once
#include <memory>
#include <optional>
#include <string>

struct sqlite3;

class RelationalDatabase {
 public:
  ~RelationalDatabase();
  explicit RelationalDatabase(sqlite3** sql);

  static std::optional<RelationalDatabase> loadDatabase(
      const std::string& dbName);

  bool createTable();
  bool exec();

 private:
  sqlite3* db;
  bool valid;
};