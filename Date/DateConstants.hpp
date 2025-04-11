namespace date_constants
{
// https://github.com/HowardHinnant/date/tree/master

static constexpr unsigned DAYS_PER_NORMAL_YEAR = 365;
static constexpr unsigned YEARS_PER_LEAP_CYCLE = 4;
static constexpr unsigned YEARS_PER_CENTURY_CYCLE = 100;
static constexpr unsigned YEARS_PER_400_CYCLE = 400;
static constexpr unsigned DAYS_PER_400_YEARS
	= (YEARS_PER_400_CYCLE * DAYS_PER_NORMAL_YEAR
		+ YEARS_PER_400_CYCLE / YEARS_PER_LEAP_CYCLE
		- YEARS_PER_400_CYCLE / YEARS_PER_CENTURY_CYCLE + 1);

static constexpr int DAYS_OFFSET_CIVIL_TO_MARCH_EPOCH = 719468;

static constexpr unsigned YOE_FORMULA_DIV_4Y = 1460;
static constexpr unsigned YOE_FORMULA_DIV_100Y = 36524;
static constexpr unsigned YOE_FORMULA_DIV_400Y = 146096;

static constexpr unsigned MONTH_CALC_MAGIC_153 = 153;
static constexpr unsigned MONTH_CALC_MAGIC_5 = 5;
static constexpr unsigned INTERNAL_MONTH_JAN_IDX = 10;
static constexpr int MONTH_ADJUST_MAR_DEC = 3;
static constexpr int MONTH_ADJUST_JAN_FEB = -9;

static constexpr unsigned CIVIL_MONTH_MAR = 3;
static constexpr int MONTH_REV_ADJUST_MAR_DEC = -3;
static constexpr int MONTH_REV_ADJUST_JAN_FEB = 9;

} // namespace date_constants
