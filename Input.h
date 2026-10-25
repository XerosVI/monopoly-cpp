#pragma once
#include <string>

// Lettura dell'input da console, sempre per righe (getline) e con validazione.
// Se lo stream termina (EOF) viene lanciata std::runtime_error.
namespace input {
    std::string testo(const std::string& domanda);
    int intero(const std::string& domanda, int min, int max);
    bool siNo(const std::string& domanda);
    void attendiInvio(const std::string& messaggio);
}
