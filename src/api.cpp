#include "../libs/httplib.h"
#include "../libs/json.hpp"
#include "simian.h"
#include "database.h"

#include <iostream>
#include <vector>
#include <string>

using json = nlohmann::json;

int main() {
    dbInit();

    httplib::Server server;

    server.Post("/simian", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Content-Type", "application/json");

        json body;
        try {
            body = json::parse(req.body);
        } catch (...) {
            res.status = 400;
            res.set_content(R"({"error":"JSON inválido"})", "application/json");
            return;
        }

        if (!body.contains("dna") || !body["dna"].is_array()) {
            res.status = 400;
            res.set_content(R"({"error":"Campo 'dna' ausente ou inválido"})", "application/json");
            return;
        }

        std::vector<std::string> dna = body["dna"].get<std::vector<std::string>>();
        bool simian = isSimian(dna);

        dbSaveDna(dna, simian);

        if (simian) {
            res.status = 200;
            res.set_content(R"({"message":"Símio detectado"})", "application/json");
        } else {
            res.status = 403;
            res.set_content(R"({"message":"Humano detectado"})", "application/json");
        }
    });

    server.Get("/stats", [](const httplib::Request&, httplib::Response& res) {
        Stats stats = dbGetStats();

        json response;
        response["count_mutant_dna"] = stats.countSimian;
        response["count_human_dna"]  = stats.countHuman;
        response["ratio"]            = stats.ratio;

        res.set_content(response.dump(), "application/json");
    });

    const int port = 8080;
    std::cout << "Servidor rodando na porta " << port << "..." << std::endl;

    if (!server.listen("0.0.0.0", port)) {
        std::cerr << "Erro: não foi possível iniciar o servidor na porta " << port << std::endl;
        return 1;
    }

    return 0;
}