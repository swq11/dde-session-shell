/*
 * Copyright (C) 2021 ~ 2022 Uniontech Software Technology Co.,Ltd.
 *
 * Author:     zhaoyingzhen <zhaoyingzhen@uniontech.com>
 *
 * Maintainer: zhaoyingzhen <zhaoyingzhen@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "virtualkeyboardmodule.h"
#include "tipcontentwidget.h"
#include "keyboardiconwidget.h"
#include "virtualkbinstance.h"
#include "public_func.h"

#include <DConfig>

DCORE_USE_NAMESPACE

VirtualKeyboardModule::VirtualKeyboardModule(QObject *parent)
    : QObject(parent)
    , m_tipContentWidget(nullptr)
    , m_keyboardIconWidget(nullptr)
{
    setObjectName("VirtualKeyboardModule");
}

VirtualKeyboardModule::~VirtualKeyboardModule()
{
    if (m_tipContentWidget) {
        delete m_tipContentWidget;
    }

    if (m_keyboardIconWidget) {
        delete m_keyboardIconWidget;
    }
}

bool VirtualKeyboardModule::isNeedInitPlugin() const
{
    // 根据配置，是否需要init插件
    DConfig *dConfig = DConfig::create(getDefaultConfigFileName(), getDefaultConfigFileName());
    dConfig->deleteLater();
    return (dConfig && !dConfig->value("hideOnboard", false).toBool());
}

void VirtualKeyboardModule::init()
{
    m_tipContentWidget = new TipContentWidget();
    m_tipContentWidget->setText(tr("virtual keyboard"));

    m_keyboardIconWidget = new KeyboardIconWidget();
    m_keyboardIconWidget->setIconPath(":/img/screen_keyboard_normal.svg");

    // 页面隐藏后，需要释放onboard进程
    connect(m_keyboardIconWidget, &KeyboardIconWidget::topLevelWidgetHided,
            &VirtualKBInstance::Instance(), &VirtualKBInstance::stopVirtualKBProcess);

    connect(m_keyboardIconWidget, &KeyboardIconWidget::iconWidgetHided,
            &VirtualKBInstance::Instance(), &VirtualKBInstance::hideKeyboardWidget);

    connect(m_keyboardIconWidget, &KeyboardIconWidget::clicked,
            &VirtualKBInstance::Instance(), &VirtualKBInstance::showKeyboardWidget);
}

QWidget *VirtualKeyboardModule::content()
{
    return nullptr;
}

QString VirtualKeyboardModule::icon() const
{
    return QString("");
}

QWidget *VirtualKeyboardModule::itemWidget() const
{
    return m_keyboardIconWidget;
}

QWidget *VirtualKeyboardModule::itemTipsWidget() const
{
    return m_tipContentWidget;
}

const QString VirtualKeyboardModule::itemContextMenu() const
{
    return QString("");
}

void VirtualKeyboardModule::invokedMenuItem(const QString &menuId, const bool checked) const
{
    Q_UNUSED(menuId)
    Q_UNUSED(checked)
}