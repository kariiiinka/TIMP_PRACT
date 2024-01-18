#include <boost/program_options.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

namespace po = boost::program_options;

class ui {
public:
    po::options_description desc;
    po::variables_map vm;
    std::vector<double> get_param();
    std::string get_operation();
    ui(int argc, char* argv[]);
};

ui::ui(int argc, char* argv[]) {
    desc.add_options()
        ("help,h", "помощь")
        ("type,t", po::value<std::string>()->multitoken(), "тип операции: summ или sub")
        ("operands,o", po::value<std::vector<double>>()->multitoken()->required(), "вводимые операнды");
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("help")) {
            std::cout << desc << std::endl;
        }
    }
    catch (po::error& e) {
        std::cout << e.what() << std::endl;
    }
}

double sum(std::vector<double> x) {
    double res = 0.0;
    for (int i = 0; i < x.size(); i++) {
        res += x[i];
    }
    return res;
}

double subs(std::vector<double> x) {
    double res = 0.0;
    double temp = x[0];
    for (int i = 1; i < x.size(); i++) {
        res += x[i];
    }
    return temp - res;
}

std::vector<double> ui::get_param() {
    if (vm.count("operands")) {
        std::vector<double> temp = vm["operands"].as<std::vector<double>>();
        if (temp.size() > 4 or temp.size() < 2) {
            std::cout << "неверное число операндов" << std::endl;
            exit(1);
        }
        return temp;
    }
    else {
        std::cout << desc << std::endl;
        exit(1);
    }
}

std::string ui::get_operation() {
    if (vm.count("type")) {
        std::string temp = vm["type"].as<std::string>();
        return temp;
    }
    else {
        std::cout << desc << std::endl;
        return "";
    }
}

int main(int argc, char* argv[]) {
    ui interface(argc, argv);
    std::vector<double> operands = interface.get_param();
    std::string operation = interface.get_operation();

    if (operation == "sub") {
        std::cout << "Резлуьтат вычитания: "<<subs(operands) << std::endl;
    }
    else if (operation == "summ") {
        std::cout <<"Результат суммы: "<< sum(operands) << std::endl;
    }
    else {
        std::cout << "Операция не определена" << std::endl;
        exit(1);
    }

    return 0;
}
