#include "code/Data.h"
#include "code/Menu.h"

int main() {
    bool quit = false;
    while (!quit) {
        Data data;
        int option;

        std::cout << "\n=================================================================================================\n";
        std::cout << " \t\t\t\t\t\t\t\t\t\tSETTING GRAPHS \n";
        std::cout << "=================================================================================================\n\n";
        std::cout << "Digite uma das seguintes opções (0-4) de acordo com o tipo de grafo deseja utilizar:\n";
        std::cout << "1- Toy Graphs\n";
        std::cout << "2- Extra Medium-Size Graphs\n";
        std::cout << "3- Real-World Graphs\n";
        std::cout << "4- Fornecer um grafo diferente (com nomes edges.csv e nodes.csv)\n";
        std::cout << "0- Sair\n";

        std::cin >> option;
        std::cin.ignore();

        if (option == 1) {
            while (!quit) {
                std::cout << "Digite uma das seguintes opções (0-3) para escolher o Toy Graph:\n";
                std::cout << "1- Shipping\n";
                std::cout << "2- Stadiums\n";
                std::cout << "3- Tourism\n";
                std::cout << "0- Sair\n";

                std::cin >> option;
                std::cin.ignore();

                quit = true;
                switch (option) {
                    case 1:
                        data.createGraph("../dataset/Toy-Graphs/shipping.csv");
                        break;

                    case 2:
                        data.createGraph("../dataset/Toy-Graphs/stadiums.csv");
                        break;

                    case 3:
                        data.createGraph("../dataset/Toy-Graphs/tourism.csv");
                        break;

                    case 0:
                        break;

                    default:
                        cout << "Digite uma opção válida!\n";
                        quit = false;
                        break;
                }
            }

            if (option != 0) Menu menu(data.getGraph(), GraphType::toyGraph);
            quit = false;
        } else if (option == 2) {
            while (!quit) {
                std::cout << "Digite uma das seguintes opções (0-12) para escolher o Extra Medium-Size Graph:\n";
                std::cout << "1-\tedges_25\n";
                std::cout << "2-\tedges_50\n";
                std::cout << "3-\tedges_75\n";
                std::cout << "4-\tedges_100\n";
                std::cout << "5-\tedges_200\n";
                std::cout << "6-\tedges_300\n";
                std::cout << "7-\tedges_400\n";
                std::cout << "8-\tedges_500\n";
                std::cout << "9-\tedges_600\n";
                std::cout << "10-\tedges_700\n";
                std::cout << "11-\tedges_800\n";
                std::cout << "12-\tedges_900\n";
                std::cout << "0-\tSair\n";

                std::cin >> option;
                std::cin.ignore();

                quit = true;
                switch (option) {
                    case 1:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_25.csv");
                        break;

                    case 2:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
                        break;

                    case 3:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_75.csv");
                        break;

                    case 4:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_100.csv");
                        break;

                    case 5:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_200.csv");
                        break;

                    case 6:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_300.csv");
                        break;

                    case 7:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_400.csv");
                        break;

                    case 8:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_500.csv");
                        break;

                    case 9:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_600.csv");
                        break;

                    case 10:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_700.csv");
                        break;

                    case 11:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_800.csv");
                        break;

                    case 12:
                        data.createMediumGraph("../dataset/Extra_Fully_Connected_Graphs/edges_900.csv");
                        break;

                    case 0:
                        break;

                    default:
                        cout << "Digite uma opção válida!\n";
                        quit = false;
                        break;
                }
            }

            if (option != 0) Menu menu(data.getGraph(), GraphType::mediumGraph);
            quit = false;
        } else if (option == 3) {
            while (!quit) {
                std::cout << "Digite uma das seguintes opções (0-3) para escolher o Real World Graph:\n";
                std::cout << "1- Graph 1\n";
                std::cout << "2- Graph 2\n";
                std::cout << "3- Graph 3\n";
                std::cout << "0- Sair\n";

                std::cin >> option;
                std::cin.ignore();

                quit = true;
                switch (option) {
                    case 1:
                        data.createRealGraph("../dataset/Real-world Graphs/graph1/edges.csv", "../dataset/Real-world Graphs/graph1/nodes.csv");
                        break;

                    case 2:
                        data.createRealGraph("../dataset/Real-world Graphs/graph2/edges.csv", "../dataset/Real-world Graphs/graph2/nodes.csv");
                        break;

                    case 3:
                        data.createRealGraph("../dataset/Real-world Graphs/graph3/edges.csv", "../dataset/Real-world Graphs/graph3/nodes.csv");
                        break;

                    case 0:
                        break;

                    default:
                        cout << "Digite uma opção válida!\n";
                        quit = false;
                        break;
                }
            }

            if (option != 0) Menu menu(data.getGraph(), GraphType::realGraph);
            quit = false;
        } else if (option == 4) {
            data.createRealGraph("../dataset/Extern-Graph/edges.csv", "../dataset/Extern-Graph/nodes.csv");
            Menu menu(data.getGraph(), GraphType::externGraph);
        } else if (option == 0) {
            quit = true;
        } else {
            cout << "Digite uma opção válida!\n";
        }
    }

    return 0;
}
