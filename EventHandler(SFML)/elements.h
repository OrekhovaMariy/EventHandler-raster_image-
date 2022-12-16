#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "form.h"
#include "common.h"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

// �������������� ���� ���������: ������, �����������, ���� ��� ����� ������
enum class ElementType { BUTTON, IMAGE, EDIT };

class Element {
public:
    // ������� ����� �������� ����� ������� ����������, ������, ���� ��������. 
    // ��������� ����� �������� - false

    explicit Element(ElementType el_type)
        : el_type_(el_type) {
    }

    // ������������� ������� ��������
    void SetElementPosition(float** a) {
        position_ = a;
    }

    // ������ ������� ��������
    float** GetElementPosition() const {
        return (float**)position_;
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
        max_point_ = p;
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
    void SetElementAngleRotation(float angle) {
        angle_rotation_ = angle;
    }

    // ������ ���� �������� ��������
    float GetElementAngleRotation() const {
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
    void Draw(sf::RenderWindow& window) const {
        sf::ConvexShape convex;

        // ������������� ���������� ������
        convex.setPointCount(4);
        // ��������� �������
        convex.setPoint(0, sf::Vector2f(position_[0][0], position_[0][1]));
        convex.setPoint(1, sf::Vector2f(position_[1][0], position_[1][1]));
        convex.setPoint(2, sf::Vector2f(position_[2][0], position_[2][1]));
        convex.setPoint(3, sf::Vector2f(position_[3][0], position_[3][1]));

        if (el_type_ == ElementType::BUTTON) {
            convex.setFillColor(sf::Color::Blue);
        }
        if (el_type_ == ElementType::EDIT) {
            convex.setFillColor(sf::Color::Green);
        }
        if (el_type_ == ElementType::IMAGE) {
            convex.setFillColor(sf::Color::Yellow);
        }
        convex.setOutlineThickness(size_.height / 100);
        convex.setOutlineColor(sf::Color::Red);
        window.draw(convex);
    }

private:
    ElementType el_type_;
    float angle_rotation_ = 0.;
    bool visible_ = false;
    Size size_ = {};
    Point max_point_ = {};
    Point min_point_ = {};
    float** position_ = nullptr;
    Point pivot_position_{ 0., 0. };
};

