#include <iostream>
#include <torch/torch.h>

int main()
{
    if (torch::cuda::is_available())
    {
        std::cout << "CUDA available! Training on GPU" << std::endl;
    }
    else
    {
        std::cout << "Training on CPU" << std::endl;
    }

    at::Tensor tensor = torch::rand({2, 3});
    std::cout << tensor << std::endl;
}
