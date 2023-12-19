#include "card_view.h"
#include "card.h"
namespace MyUno
{
    MyUno::CardView::CardView(vector<Type> acceptableTypes)
        :acceptableTypes(acceptableTypes)
    {
    }
    bool CardView::CanProcess(const Type& type)
    {
        return(std::find(acceptableTypes.begin(), acceptableTypes.end(), type) != acceptableTypes.end());
    }
}
