#include "UtilityFunctions.h"

void setAllElementsToZero(Vector<size_t>& vec) {
    for (size_t i = 0; i < vec.getCapacity(); i++) {
        vec[i] = 0;
    }
}

bool binarySearch(const Vector<size_t>& nums, int target) {
    int left = 0;
    int right = nums.getSize() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target)
            return true;

        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return false; 
}

bool isdigit(char c) {
    return (c >= '0' && c <= '9');
}
bool isStringNumber(const MyString& input) {
    bool is_number = true;
    const char* data = input.c_str();
    for (size_t i = 1; i < input.length();i++) {
        char c = data[i];
        if (!isdigit(c)) {
            is_number = false;
            break;
        }
    }
    return is_number;
}
size_t stringToSize_t(const MyString& str) {
    std::stringstream ss(str.c_str());
    size_t result;
    ss >> result;
    return result;
}