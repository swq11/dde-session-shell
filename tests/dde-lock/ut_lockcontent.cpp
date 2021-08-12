#include "lockcontent.h"
#include "sessionbasemodel.h"

#include <gtest/gtest.h>

class UT_LockContent : public testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    SessionBaseModel *m_model;
    LockContent *m_content;
};

void UT_LockContent::SetUp()
{
    m_model = new SessionBaseModel(SessionBaseModel::AuthType::LockType);
    std::shared_ptr<User> user_ptr(new User);
    m_model->updateCurrentUser(user_ptr);

    m_content = new LockContent(m_model);
}

void UT_LockContent::TearDown()
{
    delete m_content;
    delete m_model;
}

TEST_F(UT_LockContent, BasicTest)
{
    m_content->onCurrentUserChanged(m_model->currentUser());
    m_content->pushPasswordFrame();
    m_content->pushUserFrame();
    m_content->pushShutdownFrame();
    m_content->setMPRISEnable(true);
    m_content->beforeUnlockAction(false);
}

TEST_F(UT_LockContent, BackgroundTest)
{
    m_content->updateDesktopBackgroundPath("/usr/share/backgrounds/default_background.jpg");
    m_content->updateGreeterBackgroundPath("/usr/share/backgrounds/default_background.jpg");
}

TEST_F(UT_LockContent, ModeTest)
{
    m_content->onStatusChanged(SessionBaseModel::NoStatus);
    m_content->onStatusChanged(SessionBaseModel::PowerMode);
    m_content->onStatusChanged(SessionBaseModel::ConfirmPasswordMode);
    m_content->onStatusChanged(SessionBaseModel::UserMode);
    m_content->onStatusChanged(SessionBaseModel::SessionMode);
    m_content->onStatusChanged(SessionBaseModel::PowerMode);
    m_content->onStatusChanged(SessionBaseModel::ShutDownMode);
    m_content->restoreMode();
}
