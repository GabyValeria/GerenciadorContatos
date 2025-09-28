# 🚀 Gerenciador de Contatos em C

> **Status:** Projeto Concluído ✅

> **Licença:** MIT ✅

<p align="center">
  <img src="https://raw.githubusercontent.com/MicaelliMedeiros/micaellimedeiros/master/image/computer-illustration.png" alt="Ilustração de um computador" width="400"/>
</p>

Um sistema completo de gerenciamento de contatos desenvolvido em C puro, que roda diretamente no terminal. Este projeto foi criado para demonstrar e praticar conceitos fundamentais e avançados da linguagem C, resultando em uma aplicação de console robusta, eficiente e flexível.

---

## ✨ Funcionalidades Principais

**Adicionar Contatos:** Salve novos contatos com nome, telefone e e-mail.
**Listar Contatos:** Exiba todos os contatos salvos, ordenados alfabeticamente.
**Buscar Contatos:** Encontre contatos por nome (busca parcial).
**Editar Contatos:** Atualize as informações de um contato existente.
**Remover Contatos:** Exclua contatos da agenda.
**Persistência de Dados:** Salve e carregue os contatos automaticamente em um arquivo `.csv`.
**Alocação Dinâmica:** A agenda cresce conforme a necessidade, sem limite fixo de contatos.
**Validação de Entrada:** Verificação básica para formatos de e-mail e telefone.

---

## 🛠️ Tecnologias Utilizadas

Este projeto foi construído inteiramente com:

<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=c,git,github" />
  </a>
</p>

-   **Linguagem C:** Para toda a lógica do programa.
-   **GCC (GNU Compiler Collection):** Utilizado para compilar o código-fonte.
-   **Git & GitHub:** Para versionamento e hospedagem do código.

---

## ⚙️ Como Compilar e Executar

Para executar este projeto localmente, você precisará ter o compilador `gcc` instalado.

1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/GabyValeria/GerenciadorContatos.git](https://github.com/GabyValeria/GerenciadorContatos.git)
    ```

2.  **Navegue até o diretório do projeto:**
    ```bash
    cd GerenciadorContatos
    ```

3.  **Compile o código-fonte:**
    ```bash
    gcc -o gerenciador_contatos gerenciador_contatos.c -W -Wall
    ```
    * O comando acima cria um arquivo executável chamado `gerenciador_contatos`.

4.  **Execute o programa:**
    * No Linux ou macOS:
        ```bash
        ./gerenciador_contatos
        ```
    * No Windows:
        ```bash
        gerenciador_contatos.exe
        ```

---

## 📸 Demonstração em Tela

<details>
<summary><strong>Clique para ver as telas do sistema</strong></summary>

**Menu Principal:**
```
=================================
   GERENCIADOR DE CONTATOS
=================================
1. Adicionar Contato
2. Listar Contatos (Ordenado)
3. Buscar Contato
4. Remover Contato
5. Editar Contato
6. Salvar Contatos
0. Sair
---------------------------------
Contatos: 2 | Capacidade: 10
Escolha uma opção:
```

**Adicionando um novo contato:**
```
--- Adicionar Novo Contato ---
Nome: Ana Beatriz
Telefone: (11) 98765-4321
Email: ana.b@email.com

Contato adicionado com sucesso!
```

**Listando contatos (já ordenados):**
```
--- Lista de Contatos (2) ---
---------------------------------
  Nome: Ana Beatriz
  Telefone: (11) 98765-4321
  Email: ana.b@email.com
---------------------------------
  Nome: Carlos de Andrade
  Telefone: (21) 91234-5678
  Email: carlos.a@email.com
```

</details>

---

## 🚀 Melhorias Futuras

Embora o projeto esteja completo em suas funcionalidades principais, sempre há espaço para melhorias:

-   [ ] Implementar uma interface mais rica com a biblioteca `ncurses`.
-   [ ] Adicionar mais campos à `struct` de contato (ex: aniversário, empresa).
-   [ ] Criar um sistema de grupos ou categorias para os contatos.
-   [ ] Mudar o formato de salvamento para JSON ou um formato binário para maior eficiência.

---

## 📜 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

---

<p align="center">
  Desenvolvido com ❤️ por Gabrielle Souza
</p>
