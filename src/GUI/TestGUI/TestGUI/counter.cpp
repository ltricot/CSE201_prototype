#include <counter.h>

void Counter::setValue(bool value)
{
    if (value != m_value) {
        m_value = value;
        emit valueChanged(value);
    }
}
