//g++ main.cpp -o borovCalc `pkg-config gtkmm-3.0 --cflags --libs` -g

#include <iostream>
#include <gtkmm.h>

Gtk::Window* window = nullptr;
Gtk::Entry* inputOne = nullptr;
Gtk::Entry* inputTwo = nullptr;
Gtk::Entry* inputThree = nullptr;
Gtk::Entry* outputBox = nullptr;

void findPercentage() {

    Glib::ustring strDenSolute, strDenSolvent, strDenSolution;

    strDenSolute = inputOne -> get_text();
    strDenSolvent = inputTwo -> get_text();
    strDenSolution = inputThree -> get_text();

    float denSolute = std::stod(strDenSolute), denSolvent = std::stod(strDenSolvent), denSolution = std::stod(strDenSolution);

    float volSolute = (denSolution - denSolvent) / (denSolute - denSolvent);
    float volSolvent = 1 - volSolute;

    outputBox -> set_text(std::to_string(volSolvent / volSolute));

}

int main(int argc, char** argv) {

    auto app = Gtk::Application::create(argc, argv, "");

    auto refBuilder = Gtk::Builder::create();

    try {

        refBuilder->add_from_file("../res/gui.glade");

    }

        catch(const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;

    }

        catch(const Glib::MarkupError& ex)
    {

        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;

    }

        catch(const Gtk::BuilderError& ex)

    {

        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;

    }

    refBuilder -> get_widget("mainWindow", window);

    if (window) {

        Gtk::Button* calcButton = nullptr;
        refBuilder -> get_widget("calcButton", calcButton);

        refBuilder -> get_widget("inputOne", inputOne);

        refBuilder -> get_widget("inputTwo", inputTwo);

        refBuilder -> get_widget("inputThree", inputThree);

        refBuilder -> get_widget("outputBox", outputBox);

        if (calcButton) {

            calcButton -> signal_clicked().connect(sigc::ptr_fun(findPercentage));

        }

        app -> run(*window);
    }

    delete window; 
    delete inputOne; 
    delete inputTwo; 
    delete inputThree; 
    delete outputBox;
    return 0;
}
