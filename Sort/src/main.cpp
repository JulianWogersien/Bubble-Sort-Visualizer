#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

void loadFont(std::string path, sf::Font* font);
void shuffle(int* arr, int size);
void displayArray(sf::RenderWindow* window, int* arr, int size);
float map(float v, float maxScale, float minScale, float max, float min);
bool sortStep(int* arr, int size, int index);
void swap(int* i1, int* i2);

int main()
{
    unsigned int max_fps = 300;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Sorting");
    window.setFramerateLimit(max_fps);
    std::map<int, bool> keys;

    float fps;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    sf::Font font;
    loadFont("res/Roboto-Regular.ttf", &font);

    int size = 80;
    int* unsorted = new int[size];
    int* sorted = new int[size];

    for (int i = 0; i < size; i++)
    {
        unsorted[i] = i;
        sorted[i] = i;
    }

    shuffle(unsorted, size);

    bool sorting = true;
    int index = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: window.close();
            case sf::Event::KeyPressed: keys[event.key.code] = true; break;
            case sf::Event::KeyReleased: keys[event.key.code] = false; break;
            default: break;
            }
        }
        
        if (keys[sf::Keyboard::Escape]) window.close();
        if (keys[sf::Keyboard::Num2]) { sorting = true; index = 0; }
        if (keys[sf::Keyboard::Num1]) { shuffle(unsorted, size); }
        if (keys[sf::Keyboard::Up]) { max_fps += 10; std::cout << max_fps << std::endl; window.setFramerateLimit(max_fps); }

        if (sorting)
        {
            if (index < size - 1)
            {
                index++;
            }
            else
            {
                index = 0;
            }
        }
        
        if (sorting)
        {
            for (int j = 0; j < size - index - 1; j++)
            {
                sortStep(unsorted, size, index);
            }
        }

        window.clear();
        displayArray(&window, unsorted, size);
        window.display();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        std::string f = "Sorting fps:";
        f.append(std::to_string(floor(fps)));
        window.setTitle(f);
        previousTime = currentTime;
    }

    delete[] unsorted;

    return 0;
}

void loadFont(std::string path, sf::Font* font)
{
    if (!font->loadFromFile(path))
    {
        std::cout << "Error" << std::endl;
    }
}

void shuffle(int* arr, int size)
{
    std::shuffle(arr, &arr[size], std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}

void displayArray(sf::RenderWindow* window, int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        sf::RectangleShape r;
        r.setFillColor(sf::Color::White);
        r.setOutlineColor(sf::Color::White);
        r.setSize(sf::Vector2f(10, -arr[i] * 10));
        r.setPosition(i * 10, window->getSize().y);
        window->draw(r);
    }
}

float map(float v, float maxScale, float minScale, float max, float min)
{
    return (maxScale - minScale) * (v - min) / (max - min) + minScale;
}

bool sortStep(int* arr, int size, int i)
{
    if (arr[i] > arr[i + 1])
    {
        swap(&arr[i], &arr[i + 1]);
    }
    else
    {
        return false;
    }

    return true;
}

void swap(int* i1, int* i2)
{
    int t = *i1;
    *i1 = *i2;
    *i2 = t;
}
