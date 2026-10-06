// =====================================================
// DESAFIO 11 - SENSOR NO PROMPT
// =====================================================

if (pergunta.equalsIgnoreCase("wifi")) {

  int nivelSinal = WiFi.RSSI();

  String perguntaSensor =
      "O valor atual do RSSI da rede Wi-Fi e " +
      String(nivelSinal) +
      " dBm. Classifique a qualidade dessa conexao em apenas uma frase.";

  processarPergunta(perguntaSensor, "USUARIO: ");

} else {

  processarPergunta(pergunta, "USUARIO: ");

}


// =====================================================
// DESAFIO 12 - MEMORIA DE CONVERSA
// =====================================================

#define USAR_MEMORIA true
#define LIMITE_CONVERSAS 5

String historicoPerguntas[LIMITE_CONVERSAS];
String historicoRespostas[LIMITE_CONVERSAS];

int quantidadeConversas = 0;

// -----------------------------------------------------
// Salva pergunta e resposta
// -----------------------------------------------------

void salvarHistorico(const String &novaPergunta,
                     const String &novaResposta) {

  if (quantidadeConversas >= LIMITE_CONVERSAS) {

    for (int i = 0; i < LIMITE_CONVERSAS - 1; i++) {

      historicoPerguntas[i] =
          historicoPerguntas[i + 1];

      historicoRespostas[i] =
          historicoRespostas[i + 1];
    }

    quantidadeConversas--;
  }

  historicoPerguntas[quantidadeConversas] =
      novaPergunta;

  historicoRespostas[quantidadeConversas] =
      novaResposta;

  quantidadeConversas++;
}

// -----------------------------------------------------
// Adiciona historico ao JSON enviado para o Gemini
// -----------------------------------------------------

if (USAR_MEMORIA) {

  for (int i = 0; i < quantidadeConversas; i++) {

    JsonObject perguntaAnterior =
        contents.add<JsonObject>();

    perguntaAnterior["role"] = "user";

    JsonArray partesPergunta =
        perguntaAnterior["parts"].to<JsonArray>();

    partesPergunta
        .add<JsonObject>()["text"] =
        historicoPerguntas[i];



    JsonObject respostaAnterior =
        contents.add<JsonObject>();

    respostaAnterior["role"] = "model";

    JsonArray partesResposta =
        respostaAnterior["parts"].to<JsonArray>();

    partesResposta
        .add<JsonObject>()["text"] =
        historicoRespostas[i];
  }
}

// -----------------------------------------------------
// Salva a conversa atual
// -----------------------------------------------------

salvarHistorico(pergunta, String(texto));