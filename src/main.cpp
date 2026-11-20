#include <sil/sil.hpp>
#include <iostream>
#include <random.hpp>
#include <cmath>

// Workshop Prog - Pierre CASIER - IMAC3

void only_green(sil::Image &image)
{
    // sil::Image image{"images/logo.png"};
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void swap(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void black_white(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float const grey = 0.2126f * color.r + 0.7152f * color.g + 0.0722f * color.b;
        color = glm::vec3{grey};
    }
}

void neg(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.g = 1.f - color.g;
        color.b = 1.f - color.b;
    }
}

void gradient(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float const t = static_cast<float>(x) / static_cast<float>(image.width() - 1);
            image.pixel(x, y) = glm::vec3{t};
        }
    }
}

void mirror(sil::Image &image)
{
    sil::Image image_copy(image.width(), image.height());
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image_copy.pixel(x, y) = image.pixel(image.width() - 1 - x, y);
        }
    }
    image = image_copy;
}

void rotate90(sil::Image &image)
{
    sil::Image image_copy{image.height(), image.width()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image_copy.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }

    image = image_copy;
}

void noise(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (true_with_probability(0.1f))
            {
                image.pixel(x, y) = glm::vec3{
                    random_float(0.f, 1.f),
                    random_float(0.f, 1.f),
                    random_float(0.f, 1.f)};
            }
        }
    }
}

void rgb(sil::Image &image)

{
    sil::Image image_copy{image.width(), image.height()};
    const int nb_pixel{25};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image_copy.pixel(x, y).g = image.pixel(x, y).g;
            if (x + nb_pixel < image.width())
            {
                image_copy.pixel(x, y).r = image.pixel(x + nb_pixel, y).r;
            }
            if (x - nb_pixel >= 0)
            {
                image_copy.pixel(x, y).b = image.pixel(x - nb_pixel, y).b;
            }
        }
    }
    image = image_copy;
}

void light_bright(sil::Image &image)
{
    sil::Image image_copy{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image_copy.pixel(x, y).r = image.pixel(x, y).r * 1.3f;
            image_copy.pixel(x, y).g = image.pixel(x, y).g * 1.3f;
            image_copy.pixel(x, y).b = image.pixel(x, y).b * 1.3f;
        }
    }
    image = image_copy;
}
void light_dark(sil::Image &image)
{
    sil::Image image_copy{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image_copy.pixel(x, y).r = image.pixel(x, y).r / 1.3f;
            image_copy.pixel(x, y).g = image.pixel(x, y).g / 1.3f;
            image_copy.pixel(x, y).b = image.pixel(x, y).b / 1.3f;
        }
    }
    image = image_copy;
}

void disc(sil::Image &image)
{
    int const centrer_x{image.width() / 2.f};
    int const centrer_y{image.height() / 2.f};
    int const rayon{100};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int const diff_x{x - centrer_x};
            int const diff_y{y - centrer_y};
            float const distance{std::sqrt(diff_x * diff_x + diff_y * diff_y)};

            if (distance <= rayon)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

void circle(sil::Image &image)
{
    int const center_x{image.width() / 2.f};
    int const center_y{image.height() / 2.f};
    int const rayon{100};
    int const espacement{10};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int const diff_x{x - center_x};
            int const diff_y{y - center_y};
            float const distance{std::sqrt(diff_x * diff_x + diff_y * diff_y)};

            if (distance <= rayon && distance >= rayon - espacement)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

void move_disc()
{
    int nb{0};
    int count{50};
    for (nb = 0; nb < count; nb++)
    {
        sil::Image image{500, 500};
        int const centrer_x{0 + nb * 5};
        int const centrer_y{image.height() / 2.f};
        int const rayon{100};

        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                int const diff_x{x - centrer_x};
                int const diff_y{y - centrer_y};
                float const distance{std::sqrt(diff_x * diff_x + diff_y * diff_y)};

                if (distance <= rayon)
                {
                    image.pixel(x, y) = glm::vec3{1.f};
                }
            }
        }
        image.save("output/animation/movement_" + std::to_string(nb) + ".png");
    }
}

sil::Image downscale(sil::Image &image, int nb)
{
    sil::Image small{image.width() / nb, image.height() / nb};
    for (int x{0}; x < small.width(); x++)
    {
        for (int y{0}; y < small.height(); y++)
        {
            small.pixel(x, y) = image.pixel(x * nb, y * nb);
        }
    }
    return small;
}

void mosa(sil::Image &image)
{
    sil::Image image_copy{image.width(), image.height()};
    sil::Image small = downscale(image, 5);

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image_copy.pixel(x, y) = small.pixel(x % small.width(), y % small.height());
        }
    }
    image = image_copy;
}

void mosa_mirror(sil::Image &image)
{
    sil::Image image_copy{image.width(), image.height()};
    sil::Image small = downscale(image, 5);

    int conteur_x = 0;
    for (int x{0}; x < image.width(); x++)
    {
        if (x != 0 && x % small.width() == 0)
        {
            conteur_x++;
        }
        int conteur_y = 0;
        for (int y{0}; y < image.height(); y++)
        {
            if (y != 0 && y % small.height() == 0)
            {
                conteur_y++;
            }
            int vrai_x;
            int vrai_y;
            if (conteur_x % 2 == 0)
            {
                vrai_x = x % small.width();
            }
            else
            {

                vrai_x = small.width() - 1 - x % small.width();
            }
            if (conteur_y % 2 == 0)
            {
                vrai_y = y % small.height();
            }
            else
            {

                vrai_y = small.height() - 1 - y % small.height();
            }
            image_copy.pixel(x, y) = small.pixel(vrai_x, vrai_y);
        }
    }
    image = image_copy;
}

void glitch(sil::Image &image)
{
    int const nb_glitchs{30};
    int const largeur{random_int(10, 60)};
    int const hauteur{random_int(3, 15)};

    for (int i{0}; i < nb_glitchs; i++)
    {
        int const coin_x1{random_int(0, image.width() - largeur)};
        int const coin_y1{random_int(0, image.height() - hauteur)};
        int const coin_x2{random_int(0, image.width() - largeur)};
        int const coin_y2{random_int(0, image.height() - hauteur)};

        for (int diff_x{0}; diff_x < largeur; diff_x++)
        {
            for (int diff_y{0}; diff_y < hauteur; diff_y++)
            {
                std::swap(image.pixel(coin_x1 + diff_x, coin_y1 + diff_y), image.pixel(coin_x2 + diff_x, coin_y2 + diff_y));
            }
        }
    }
}

void bonus_cercles(sil::Image &image)
{
    int const center_x{(image.width() - 1) / 2};
    int const center_y{(image.height() - 1) / 2};
    int const espacement{30};
    int const epaisseur{6};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int const diff_x{x - center_x};
            int const diff_y{y - center_y};
            int const distance{std::sqrt(diff_x * diff_x + diff_y * diff_y)};

            int const reste{distance % espacement};

            if (reste < epaisseur)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

void bonus_spirale(sil::Image &image)
{
    float const center_x{(image.width() - 1) / 2.f};
    float const center_y{(image.height() - 1) / 2.f};
    float const espacement{30.f}; // écart entre deux tours de spirale
    float const epaisseur{6.f};
    float const pi{3.1415f};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float const diff_x{x - center_x};
            float const diff_y{y - center_y};
            float const distance{std::sqrt(diff_x * diff_x + diff_y * diff_y)};
            float const angle{std::atan2(diff_y, diff_x)};

            float const decale{angle / (2.f * pi) * espacement};
            float const reste{std::fmod(distance - decale + 10 * espacement, espacement)};

            if (reste < epaisseur)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        only_green(image);                   // Utilise la fonction pour modifier l'image
        image.save("output/only_green.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"};
        swap(image);
        image.save("output/swap.png");
    }
    {
        sil::Image image("images/logo.png");
        black_white(image);
        image.save("output/black_white.png");
    }
    {
        sil::Image image("images/logo.png");
        neg(image);
        image.save("output/neg.png");
    }
    {
        sil::Image image{300, 200};
        gradient(image);
        image.save("output/gradient.png");
    }
    {
        sil::Image image("images/logo.png");
        mirror(image);
        image.save("output/mirror.png");
    }
    {
        sil::Image image("images/logo.png");
        rotate90(image);
        image.save("output/rotate90.png");
    }
    {
        sil::Image image("images/logo.png");
        noise(image);
        image.save("output/noise.png");
    }
    {
        sil::Image image("images/logo.png");
        rgb(image);
        image.save("output/rgb.png");
    }
    {
        sil::Image image("images/photo_faible_contraste.jpg");
        light_bright(image);
        image.save("output/light_bright.png");
    }
    {
        sil::Image image("images/photo_faible_contraste.jpg");
        light_dark(image);
        image.save("output/light_dark.png");
    }
    {
        sil::Image image{500, 500};
        disc(image);
        image.save("output/disc.png");
    }
    {
        sil::Image image{500, 500};
        circle(image);
        image.save("output/circle.png");
    }

    move_disc();

    {
        sil::Image image("images/logo.png");
        mosa(image);
        image.save("output/mosa.png");
    }
    {
        sil::Image image("images/logo.png");
        mosa_mirror(image);
        image.save("output/mosa_mirror.png");
    }
    {
        sil::Image image("images/logo.png");
        glitch(image);
        image.save("output/glitch.png");
    }
    {
        sil::Image image{500, 500};
        bonus_cercles(image);
        image.save("output/bonus_cercles.png");
    }
    {
        sil::Image image{500, 500};
        bonus_spirale(image);
        image.save("output/bonus_spirale.png");
    }
}
