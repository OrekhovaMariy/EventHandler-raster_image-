#pragma once
#include "form.h"
#include "common.h"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

// �������������� ���� ���������: ������, �����������, ���� ��� ����� ������
enum class ElementType { BUTTON, IMAGE, EDIT};

class Element {
public:
    // ������� ����� �������� ����� ������� ����������, ������, ���� ��������. 
    // ��������� ����� �������� - false
    
    explicit Element(ElementType el_type)
        : el_type_(el_type) {
    }

    // ������������� ������� ��������
    void SetElementPosition(int** a) {
        position_ = a;
    }

    // ������ ������� ��������
    int** GetElementPosition() const {
        return (int**)position_;
    }

    // ������������� ������� ����� ��������
    void SetPivotPosition(Point pivot_position) {
        pivot_position_ = pivot_position;
    }

    // ������ ������� ����� ��������
    Point GetPivotPosition() const {
        return pivot_position_;
    }

    // ������������� ������ ��������
    void SetElementSize(Size size) {
            size_ = size;
    }

    // ������ ������ ��������
    Size GetElementSize() {
        return size_;
    }

    // ������������� ������������ �������, ������� ������������� ������� �����
    void SetElementMaxPoint(Point p) {
        max_point_= p;
    }

    // ������ ������������ �������, ������� ������������� ������� �����
    Point GetElementMaxPoint() {
        return max_point_;
    }

    // ������������� ����������� �������, ������� ������������� ������� �����
    void SetElementMinPoint(Point p) {
        min_point_ = p;
    }

    // ������ ����������� �������, ������� ������������� ������� �����
    Point GetElementMinPoint() {
        return min_point_;
    }

    // ������������� ���� �������� ��������
    void SetElementAngleRotation(double angle) {
        angle_rotation_ = angle;
    }

    // ������ ���� �������� ��������
    double GetElementAngleRotation() const {
        return angle_rotation_;
    }

    // ������ ������� �������
    void MakeElementVisible() {
        visible_ = true;
    }

    // ������ ������� �� �������
    void MakeElementUnvisible() {
        visible_ = false;
    }

    // ������ ������ ��������� ��������
    bool GetElementVisibility() {
        return visible_;
    }

    // ������ ��� ��������
    ElementType GetElementType() {
        return el_type_;
    }

// ������ ���������� �������������
    void Draw(char** image) const {

            if (el_type_ == ElementType::BUTTON) {

                Brezenhem(image, position_[0][0], position_[0][1], position_[1][0], position_[1][1], 'B');
                Brezenhem(image, position_[1][0], position_[1][1], position_[2][0], position_[2][1], 'B');
                Brezenhem(image, position_[2][0], position_[2][1], position_[3][0], position_[3][1], 'B');
                Brezenhem(image, position_[3][0], position_[3][1], position_[0][0], position_[0][1], 'B');
            }
            if (el_type_ == ElementType::EDIT) {
                Brezenhem(image, position_[0][0], position_[0][1], position_[1][0], position_[1][1], 'E');
                Brezenhem(image, position_[1][0], position_[1][1], position_[2][0], position_[2][1], 'E');
                Brezenhem(image, position_[2][0], position_[2][1], position_[3][0], position_[3][1], 'E');
                Brezenhem(image, position_[3][0], position_[3][1], position_[0][0], position_[0][1], 'E');
            }
            if (el_type_ == ElementType::IMAGE) {
                Brezenhem(image, position_[0][0], position_[0][1], position_[1][0], position_[1][1], 'I');
                Brezenhem(image, position_[1][0], position_[1][1], position_[2][0], position_[2][1], 'I');
                Brezenhem(image, position_[2][0], position_[2][1], position_[3][0], position_[3][1], 'I');
                Brezenhem(image, position_[3][0], position_[3][1], position_[0][0], position_[0][1], 'I');
            }
    }

private:
    ElementType el_type_;
    double angle_rotation_ = 0;
    bool visible_ = false;
    Size size_ = {};
    Point max_point_ = {};
    Point min_point_ = {};
    int** position_ = nullptr;
    Point pivot_position_{ 0, 0 };
};

