#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "form.h"

#include <iostream>
#include <map>
#include <string_view>
#include <stdexcept>

//���� �����������


class EventHandler {
public:
    explicit EventHandler(Size size, sf::RenderWindow& window)
        : size_(size)
        , window_(window) {
    }

    // ��������� � ���������� ����� � ������������ ��������� � ������������ ��������
    void AddFormInLine(Point pos, Size size) {

        auto form_ptr = std::make_shared<Form>(pos, size);
        // �����  ����������� � ������� ��� �������� �����������.
        if (!line_of_forms_.empty()) {
            line_of_forms_[id_of_active_form]->MakeFormUnactive();
        }
        line_of_forms_[current_id_] = std::move(form_ptr);
        line_of_forms_[current_id_]->MakeFormActive();
        id_of_active_form = current_id_;
        current_id_++;

    }

    // ������ ���������� ����� � ����������� �� �� ��������
    void MakeFormInHandlerUnactive(size_t id) {
        if (line_of_forms_.count(id)) {
            line_of_forms_[id]->MakeFormUnactive();
            if (line_of_forms_.size() > 1) {
                if (GetFormNodeById(id) != std::prev(line_of_forms_.end())) {
                    id_of_active_form = std::prev(line_of_forms_.end())->first;
                }
                else {
                    id_of_active_form = std::prev(GetFormNodeById(id))->first;
                }
            }
            else {
                id_of_active_form = 0;
            }
        }
        else {
            throw std::out_of_range("No element with given ID");
        }
    }

    // ������� ����� �� �����������
    void DeleteForm(size_t id) {
        auto it = GetFormNodeById(id);
        // ���� ����� ���������� �������� ���� �������, �� ����� � �� ��������.
        if (it->second->GetFormActivities()) {
            MakeFormInHandlerUnactive(id);
        }
        line_of_forms_.erase(GetFormNodeById(id));
    }

    // ���������� ������ � �����������
    void Click(Point pos_of_mouse) {
        std::cout << "pos_of_mouse = {"s << pos_of_mouse.x << ","s << pos_of_mouse.y << "} "s;
        // ��������, ����������� �� ���� �� ���������� �����������
        if (IsPointInRestangle(pos_of_mouse, size_.width, 0, size_.height, 0)) {
            if (!line_of_forms_.empty()) {
                size_t last_id_of_active_form = id_of_active_form;
                if (line_of_forms_.count(id_of_active_form)) {
                    auto& it = line_of_forms_.at(id_of_active_form);
                    // ��������, ����������� �� ���� �� ���������� �����. ������� � ��������.
                    if (IsPointInRestangle(pos_of_mouse, it->GetFormSize().width + it->GetFormPosition().x,
                        it->GetFormPosition().x, it->GetFormSize().height + it->GetFormPosition().y, it->GetFormPosition().y)) {
                        std::cout << "Form " << id_of_active_form << ". ";
                        it->HandlerOfElements(pos_of_mouse);
                        std::cout << std::endl;
                    }
                    else {
                        // ���� ����� �� �������, �� �������� � � �������� �����
                        for (size_t i = 0; i < last_id_of_active_form; ++i) {
                            if (line_of_forms_.count(i)) {
                                auto& t = line_of_forms_.at(i);
                                if (IsPointInRestangle(pos_of_mouse, t->GetFormSize().width + t->GetFormPosition().x,
                                    t->GetFormPosition().x, t->GetFormSize().height + t->GetFormPosition().y, t->GetFormPosition().y)) {
                                    line_of_forms_[id_of_active_form]->MakeFormUnactive();
                                    t->MakeFormActive();
                                    id_of_active_form = i;
                                }
                            }
                        }
                        for (size_t i = last_id_of_active_form + 1; i < line_of_forms_.size(); ++i) {
                            if (line_of_forms_.count(i)) {
                                auto& t = line_of_forms_.at(i);
                                if (IsPointInRestangle(pos_of_mouse, t->GetFormSize().width + t->GetFormPosition().x,
                                    t->GetFormPosition().x, t->GetFormSize().height + t->GetFormPosition().y, t->GetFormPosition().y)) {
                                    line_of_forms_[id_of_active_form]->MakeFormUnactive();
                                    t->MakeFormActive();
                                    id_of_active_form = i;
                                }
                            }
                        }
                    }
                }
            }
        }
        std::cout << endl;
    }

    // ������� ������ ���� �� ������
    void PrintLineOfForms(sf::RenderWindow& window) const {
        for (size_t i = 0; i < id_of_active_form; ++i) {
            if (line_of_forms_.count(i)) {
                line_of_forms_.at(i)->DrawForm(window);
            }
        }
        for (size_t i = id_of_active_form + 1; i < line_of_forms_.size(); ++i) {
            if (line_of_forms_.count(i)) {
                line_of_forms_.at(i)->DrawForm(window);
            }
        }
        if (line_of_forms_.count(id_of_active_form)) {
            line_of_forms_.at(id_of_active_form)->DrawForm(window);
        }
    }

    // ������ � ������������ ����� � ������� �� � id � �������������� ���������
    std::unordered_map<size_t, std::shared_ptr<Form>>::iterator GetFormNodeById(size_t id) {
        auto it = line_of_forms_.find(id);
        if (it == line_of_forms_.end()) {
            throw std::out_of_range("No form with given ID");
        }
        return it;
    }

private:
    sf::RenderWindow& window_;
    size_t id_of_active_form = 0;
    Size size_{};
    size_t current_id_ = 0;
    std::unordered_map<size_t, std::shared_ptr<Form>> line_of_forms_;
};
