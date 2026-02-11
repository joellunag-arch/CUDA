#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <optional> 
#include <cstdint>  

// Declaramos la función externa de CUDA
// Nota: std::uint8_t es lo mismo que unsigned char
extern "C" void aplicarBlurCUDA(std::uint8_t* pixels, int width, int height);

int main() {
    sf::Image originalImage;
    if (!originalImage.loadFromFile("imagen.png")) {
        std::cerr << "Error: No se encontro 'imagen.png'" << std::endl;
        return -1;
    }

    sf::Image currentImage = originalImage;
    sf::Vector2u size = originalImage.getSize();
    
    unsigned int width = size.x;
    unsigned int height = size.y;

    sf::Texture texture;
    
    if (!texture.loadFromImage(currentImage)) return -1;
    
    sf::Sprite sprite(texture);

    
    sf::RenderWindow window(sf::VideoMode({width, height}), "Examen CUDA Blur");

    // Loop principal
    while (window.isOpen()) {
        
        
        while (const std::optional event = window.pollEvent()) {
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                
                if (keyEvent->code == sf::Keyboard::Key::B) {
                    std::cout << "Aplicando Blur con CUDA..." << std::endl;

                    std::uint8_t* ptr = const_cast<std::uint8_t*>(currentImage.getPixelsPtr());

                    aplicarBlurCUDA(ptr, width, height);

                    texture.update(currentImage);
                    std::cout << "Efecto aplicado." << std::endl;
                }

                if (keyEvent->code == sf::Keyboard::Key::R) {
                    std::cout << "Reseteando imagen..." << std::endl;
                    currentImage = originalImage;
                    texture.update(currentImage);
                }
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}