#include <iostream>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    std::string text_to_hide = "Hello world";
    std::vector<char> _4bits_vector{};
    cv::Mat mat_of_img = cv::imread("images_before_lsb/tanks.bmp", cv::IMREAD_COLOR);
    if(mat_of_img.data == NULL)
    {
        std::cout << "Can't open image to read!" << "\n";
    }
    else
    {
        std::cout << "Started proccesing image!" << "\n";
        std::cout << mat_of_img.rows << "\n";
        for(int i = 0; i < text_to_hide.size(); ++i)
        {
           char _8bits = text_to_hide[i];
           char last_4_bits = _8bits;
           last_4_bits = last_4_bits >> 4;
           _4bits_vector.push_back(last_4_bits);
           char first_4_bits = _8bits;
           first_4_bits = first_4_bits & 0b00001111;
           _4bits_vector.push_back(first_4_bits);
        }
        int col = 0;
        int rows = mat_of_img.rows;
        int row = 0;
        for(char _4bits : _4bits_vector)
        {
            if(row <= rows)
            {
                mat_of_img.at<cv::Vec3b>(col, row)[0] = mat_of_img.at<cv::Vec3b>(col, row)[0] & 0b11110000;
                mat_of_img.at<cv::Vec3b>(col, row)[0] = mat_of_img.at<cv::Vec3b>(col, row)[0] | _4bits;
                row++;
            }
            else
            {
                col++;
                row = 0;
                mat_of_img.at<cv::Vec3b>(col, row)[0] = mat_of_img.at<cv::Vec3b>(col, row)[0] & 0b11110000;
                mat_of_img.at<cv::Vec3b>(col, row)[0] = mat_of_img.at<cv::Vec3b>(col, row)[0] | _4bits;
            }
        }
        cv::imshow("yab", mat_of_img);
        cv::waitKey();
        int bytes_coded = _4bits_vector.size();
        std::string coded_text = "";
        int col_d = 0;
        int row_d = 0;
        for(int i = 0; i < bytes_coded / 2; ++i)
        {
            if(row_d <= rows)
            {
                char last_4_bits = mat_of_img.at<cv::Vec3b>(col_d, row_d)[0];
                last_4_bits = last_4_bits << 4;
                row_d++;
                char first_4_bits = mat_of_img.at<cv::Vec3b>(col_d, row_d)[0];
                first_4_bits = first_4_bits & 0b00001111;
                row_d++;
                char _1_sym = last_4_bits | first_4_bits;
                std::string tmp_str(1, _1_sym);
                std::cout << int(_1_sym) << " ";
            }
            else
            {
                row_d = 0;
                col_d++;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
