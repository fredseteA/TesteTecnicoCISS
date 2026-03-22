#include "database.h"
#include <sqlite3.h>
#include <sstream>
#include <iostream>

static const char* DB_PATH = "/data/simian.db";

static std::string dnaToString(const std::vector<std::string>& dna) {
    std::ostringstream oss;
    for (size_t i = 0; i < dna.size(); i++) {
        if (i > 0) oss << ",";
        oss << dna[i];
    }
    return oss.str();
}

void dbInit() {
    sqlite3* db;
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) {
        std::cerr << "Erro ao abrir banco: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS dna_records ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "dna TEXT UNIQUE NOT NULL,"
        "is_simian INTEGER NOT NULL"
        ");";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erro ao criar tabela: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}

void dbSaveDna(const std::vector<std::string>& dna, bool isSimian) {
    sqlite3* db;
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) return;

    std::string dnaStr = dnaToString(dna);

    const char* sql = "INSERT OR IGNORE INTO dna_records (dna, is_simian) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, dnaStr.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, isSimian ? 1 : 0);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
}

Stats dbGetStats() {
    Stats stats = {0, 0, 0.0f};
    sqlite3* db;
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) return stats;

    const char* sql =
        "SELECT "
        "SUM(CASE WHEN is_simian = 1 THEN 1 ELSE 0 END) as simian, "
        "SUM(CASE WHEN is_simian = 0 THEN 1 ELSE 0 END) as human "
        "FROM dna_records;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            stats.countSimian = sqlite3_column_int(stmt, 0);
            stats.countHuman  = sqlite3_column_int(stmt, 1);
            int total = stats.countSimian + stats.countHuman;
            stats.ratio = total > 0 ? (float)stats.countSimian / total : 0.0f;
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return stats;
}