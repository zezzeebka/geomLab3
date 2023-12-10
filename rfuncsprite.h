#ifndef RFUNCSPRITE_H
#define RFUNCSPRITE_H


#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <cmath>
struct info
    {
        float z;
        float nx;
        float ny;
        float nz;
        float nw;
    };
class RFuncSprite: public sf::Sprite
{
public:
    RFuncSprite();
                 // Выставим текстуру для нашего спрайта}
    void Create(const sf::Vector2u& size);



    void computeNormals(int i, int j, const sf::FloatRect& subSpace, sf::Vector2f spaceStep);

    void DrawRFunc(const std::function<float(const sf::Vector2f&)>& rfunc,  const sf::FloatRect& subSpace, int _normalType);
    void render(sf::RenderWindow& window, int imageNum);
    void gradientDescent(unsigned int x, unsigned int y, int normalType);
    void computeGradient(int x, int y, double& gradientX, double& gradientY, int normalType);
    void HandleEvent(sf::Event& event, sf::RenderWindow& window, int normalType);
    void gradientClear();
    sf::Image getImage(int _normalType)
    {
        switch(_normalType){
        case 0:
        return _image;
        case 1:
        return _imageX;
        case 2:
        return _imageY;
        case 3:
        return _imageZ;
        case 4:
        return _imageW;
        default:
            return _image;
        }
    }

private:
    sf::Texture _texture;
    sf::Image _image;
    sf::Image _imageX;
    sf::Image _imageY;
    sf::Image _imageZ;
    sf::Image _imageW;
    std::vector<std::vector<info>> m_rect;
    int _size;
    const double learning_rate = 100;
    const int max_iterations = 1000;
    //const double gradient_threshold = 0.0035;

    std::vector<sf::Sprite*> gradLines;
};
#endif // RFUNCSPRITE_H

