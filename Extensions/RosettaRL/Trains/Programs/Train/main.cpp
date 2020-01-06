// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Judges/JSON/Reader.hpp>
#include <NeuralNet/NeuralNetwork.hpp>

#include <effolkronium/random.hpp>
#include <json/json.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace RosettaTorch;

class Trainer
{
 public:
    Trainer()
    {
        NeuralNet::NeuralNetwork::CreateWithRandomWeights("initial_model");
        m_net.Load("initial_model");
    }

    void AddJSONFile(const std::string& fileName, bool forValidate)
    {
        nlohmann::json obj;
        std::ifstream fs(fileName);
        fs >> obj;

        Judges::JSON::Reader gameReader;
        gameReader.Parse(
            obj,
            [&](const Judges::JSON::NeuralNetInputGetter& input, int label) {
                if (forValidate)
                {
                    m_validateInput.AddData(&input);
                    m_validateOutput.AddData(label);
                }
                else
                {
                    m_trainInput.AddData(&input);
                    m_trainOutput.AddData(label);
                }
            });
    }

    void Train() const
    {
        const std::size_t batchSize = 32;
        const std::size_t epoch = 10;
        std::size_t totalEpoch = 0;

        while (true)
        {
            m_net.Train(m_trainInput, m_trainOutput, batchSize, epoch);
            totalEpoch += epoch;

            std::stringstream ss;
            ss << "net_result_epoch_" << totalEpoch;
            m_net.Save(ss.str());

            {
                const auto trainVerify =
                    m_net.Verify(m_trainInput, m_trainOutput);
                const double rate =
                    static_cast<double>(trainVerify.first) / trainVerify.second;
                std::cout << "Test data correct rate: " << rate * 100.0 << "% ("
                          << trainVerify.first << " / " << trainVerify.second
                          << ")" << std::endl;
            }

            {
                const auto validateVerify =
                    m_net.Verify(m_validateInput, m_validateOutput);
                const double rate = static_cast<double>(validateVerify.first) /
                                    validateVerify.second;
                std::cout << "Validation data correct rate: " << rate * 100.0
                          << "% (" << validateVerify.first << " / "
                          << validateVerify.second << ")" << std::endl;
            }
        }
    }

 private:
    NeuralNet::NeuralNetwork m_net;
    NeuralNet::NeuralNetworkInput m_trainInput;
    NeuralNet::NeuralNetworkOutput m_trainOutput;
    NeuralNet::NeuralNetworkInput m_validateInput;
    NeuralNet::NeuralNetworkOutput m_validateOutput;
};

using Random = effolkronium::random_static;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: (program) (dir name)" << std::endl;
        return EXIT_FAILURE;
    }

    Trainer trainer;

    const std::string dirName = argv[1];
    const std::string fileListPath = dirName + "/filelist";

    std::cout << "Reading from dir: " << dirName << std::endl;
    std::cout << "Filelist file: " << fileListPath << std::endl;

    std::ifstream fileList(fileListPath);

    int loadedFiles = 0;
    const double validationCaseRate = 0.3;  // 30% for validation

    while (fileList)
    {
        std::string fileName;
        fileList >> fileName;

        if (fileName.empty())
        {
            continue;
        }

        const auto randValue = Random::get<double>(0.0, 1.0);
        const bool forValidate = randValue < validationCaseRate;

        try
        {
            trainer.AddJSONFile(dirName + "/" + fileName, forValidate);
        }
        catch (...)
        {
            std::cout << "Failed when loading file " << fileName << std::endl;
            throw;
        }

        ++loadedFiles;
        if (loadedFiles % 100 == 0)
        {
            std::cout << "Loaded " << loadedFiles << " files" << std::endl;
        }
    }

    trainer.Train();

    return EXIT_SUCCESS;
}