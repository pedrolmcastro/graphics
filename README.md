# Graphics

Esse projeto foi desenvolvido como trabalho da disciplina **SCC0250 - Computação Gráfica** e também pode ser encontrado no [GitHub](https://github.com/pedrolmcastro/graphics).

- Álvaro José Lopes                  - 10873365
- Natan Henrique Sanches             - 11795680
- Gabriel da Cunha Dertoni           - 11795717
- Pedro Lucas de Moliner de Castro   - 11795784
- João Guilherme Jarochinski Marinho - 10698193


## Compilação e execução

Para compilação desse projeto, é necessário primeiro ter instalado o [GNU Make](https://www.gnu.org/software/make/) e então executar os seguintes comandos dentro do diretório [Project/](Project/):

```bash
make dep # Instala as dependências e inicia os submodulos
make     # Compila a aplicação
make run # Executa a aplicação
```


## Interagindo com a aplicação

O programa é composto por quatro cenas, as três primeiras têm um objetivo a ser cumprido e podem ser controladas utilizando as setas, já a quarta é uma simulação de [Boids](https://en.wikipedia.org/wiki/Boids) que fogem do cursor do mouse e podem ser gerados com clicks.


## Dependências

Essa aplicação depende dos seguintes projetos abertos para uso. As licenças referentes a tais dependências podem ser encontradas no diretório [Licenses/](Licenses/).

- [GLM](https://github.com/g-truc/glm)
- [GLEW](https://glew.sourceforge.net/)
- [GLFW](https://www.glfw.org/)
