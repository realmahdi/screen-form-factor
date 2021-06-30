#ifndef SCREENFORMFACTOR_H
#define SCREENFORMFACTOR_H

#include <QQuickItem>
#include <QtMath>

class screenformfactor : public QQuickItem
{

    Q_OBJECT

    Q_PROPERTY(e_form_factor form_factor READ get_form_factor NOTIFY form_factor_changed)
    Q_PROPERTY(bool is_phone READ is_phone NOTIFY is_phone_changed)
    Q_PROPERTY(bool is_phablet READ is_phablet NOTIFY is_phablet_changed)
    Q_PROPERTY(bool is_tablet READ is_tablet NOTIFY is_tablet_changed)
    Q_PROPERTY(bool is_desktop READ is_desktop NOTIFY is_desktop_changed)
    Q_PROPERTY(bool is_tv READ is_tv NOTIFY is_tv_changed)

public:
    screenformfactor(QQuickItem *parent=Q_NULLPTR);

    enum e_form_factor { NONE, PHONE, PHABLET, TABLET, DESKTOP, TV };
    Q_ENUM(e_form_factor)

    e_form_factor get_form_factor();
    static void register_screenformfactor();

    void set_is_phone(bool is_phone);
    void set_is_phablet(bool is_phablet);
    void set_is_tablet(bool is_tablet);
    void set_is_desktop(bool is_desktop);
    void set_is_tv(bool is_tv);

    Q_INVOKABLE void force_detect();

private:
    qreal old_width = 0;
    screenformfactor::e_form_factor m_form_factor;

    bool is_phone() const;
    bool is_phablet() const;
    bool is_tablet() const;
    bool is_desktop() const;
    bool is_tv() const;

    bool m_is_phone;
    bool m_is_phablet;
    bool m_is_tablet;
    bool m_is_desktop;
    bool m_is_tv;

public slots:
    void set_form_factor(bool force = false);
    void parent_changed(QQuickItem* item);

signals:
    void form_factor_changed(const e_form_factor form_factor);
    void is_phone_changed();
    void is_phablet_changed();
    void is_tablet_changed();
    void is_desktop_changed();
    void is_tv_changed();
};

#endif // SCREENFORMFACTOR_H
