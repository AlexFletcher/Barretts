#include "ExponentialCellCycleModel.hpp"

ExponentialCellCycleModel::ExponentialCellCycleModel()
    : AbstractSimpleCellCycleModel(),
      mRate(1.0)
{
}

ExponentialCellCycleModel::ExponentialCellCycleModel(const ExponentialCellCycleModel& rModel)
   : AbstractSimpleCellCycleModel(rModel),
     mRate(rModel.mRate)
{
    /*
     * Initialize only those member variables defined in this class.
     *
     * The member variable mCellCycleDuration is initialized in the
     * AbstractSimpleCellCycleModel constructor.
     *
     * The member variables mBirthTime, mReadyToDivide and mDimension
     * are initialized in the AbstractCellCycleModel constructor.
     *
     * Note that mCellCycleDuration is (re)set as soon as
     * InitialiseDaughterCell() is called on the new cell-cycle model.
     */
}

AbstractCellCycleModel* ExponentialCellCycleModel::CreateCellCycleModel()
{
    return new ExponentialCellCycleModel(*this);
}

void ExponentialCellCycleModel::SetCellCycleDuration()
{
    mCellCycleDuration = RandomNumberGenerator::Instance()->ExponentialRandomDeviate(mRate);
}

void ExponentialCellCycleModel::SetRate(double rate)
{
    mRate = rate;
}

double ExponentialCellCycleModel::GetAverageTransitCellCycleTime()
{
    return 1.0/mRate;
}

double ExponentialCellCycleModel::GetAverageStemCellCycleTime()
{
    return 1.0/mRate;
}

void ExponentialCellCycleModel::OutputCellCycleModelParameters(out_stream& rParamsFile)
{
    *rParamsFile << "\t\t\t<Rate>" << mRate << "</Rate>\n";
    AbstractSimpleCellCycleModel::OutputCellCycleModelParameters(rParamsFile);
}

// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(ExponentialCellCycleModel)
