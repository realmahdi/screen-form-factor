#include "screenformfactor.h"

screenformfactor::screenformfactor(QQuickItem *parent): QQuickItem(parent)
{
    connect(this, &screenformfactor::parentChanged, this, &screenformfactor::parent_changed);
}

void screenformfactor::register_screenformfactor()
{
    qmlRegisterType<screenformfactor>("formfactor", 1, 0, "FormFactorHandler");
}

bool screenformfactor::is_phone() const
{
    return m_is_phone;
}

bool screenformfactor::is_phablet() const
{
    return m_is_phablet;
}

bool screenformfactor::is_tablet() const
{
    return m_is_tablet;
}

bool screenformfactor::is_desktop() const
{
    return m_is_desktop;
}

bool screenformfactor::is_laptop() const
{
    return m_is_laptop;
}

void screenformfactor::force_detect()
{
    if (!this->parentItem())
        return;

    this->m_is_desktop = false;
    this->m_is_laptop = false;
    this->m_is_phablet = false;
    this->m_is_tablet = false;
    this->m_is_phone = false;
    this->m_form_factor = e_form_factor::NONE;
    set_form_factor(true);
}

void screenformfactor::set_is_desktop(bool is_desktop)
{
    if (is_desktop == m_is_desktop)
        return;
    m_is_desktop = is_desktop;
    emit is_desktop_changed();
}

void screenformfactor::set_is_laptop(bool is_laptop)
{
    if (is_laptop == m_is_laptop)
        return;
    m_is_laptop = is_laptop;
    emit is_laptop_changed();
}

void screenformfactor::set_is_tablet(bool is_tablet)
{
    if (is_tablet == m_is_tablet)
        return;
    m_is_tablet = is_tablet;
    emit is_tablet_changed();
}

void screenformfactor::set_is_phablet(bool is_phablet)
{
    if (is_phablet == m_is_phablet)
        return;
    m_is_phablet = is_phablet;
    emit is_phablet_changed();
}

void screenformfactor::set_is_phone(bool is_phone)
{
    if (is_phone == m_is_phone)
        return;
    m_is_phone = is_phone;
    emit is_phone_changed();
}

screenformfactor::e_form_factor screenformfactor::get_form_factor()
{
    return m_form_factor;
}

void screenformfactor::parent_changed(QQuickItem *item)
{
    if (!item)
        return;

    connect(item, SIGNAL(widthChanged()), this, SLOT(set_form_factor()));
}

void screenformfactor::set_form_factor(bool force)
{
    if (!force && qFabs(old_width - parentItem()->width()) < 15)
        return;

    old_width = parentItem()->width();
    qreal _width = parentItem()->width();

    e_form_factor new_form_factor = e_form_factor::NONE;
    if (_width >= 0 && _width <= 599)
    {
        new_form_factor = screenformfactor::PHONE;
    }
    else if (_width >= 600 && _width <= 719)
    {
        new_form_factor = screenformfactor::PHABLET;
    }
    else if (_width >= 720 && _width <= 1239)
    {
        new_form_factor = screenformfactor::TABLET;
    }
    else if (_width >= 1240 && _width <= 1439)
    {
        new_form_factor = screenformfactor::LAPTOP;
    }
    else if (_width >= 1440)
    {
        new_form_factor = screenformfactor::DESKTOP;
    }

    if (new_form_factor == m_form_factor)
        return;

    m_form_factor = new_form_factor;

    set_is_phone((m_form_factor == screenformfactor::PHONE));
    set_is_phablet((m_form_factor == screenformfactor::PHABLET));
    set_is_tablet((m_form_factor == screenformfactor::TABLET));
    set_is_laptop((m_form_factor == screenformfactor::LAPTOP));
    set_is_desktop((m_form_factor == screenformfactor::DESKTOP));

    emit form_factor_changed(m_form_factor);
}
