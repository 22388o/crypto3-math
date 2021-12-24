//---------------------------------------------------------------------------//
// Copyright (c) 2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2021 Nikita Kaskov <nbering@nil.foundation>
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#define BOOST_TEST_MODULE expression_arithmetic_test

#include <cmath>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <nil/crypto3/algebra/fields/arithmetic_params/bls12.hpp>

#include <nil/crypto3/math/polynomial/polynom.hpp>
#include <nil/crypto3/math/expressions/qi/expression.hpp>

using namespace nil::crypto3::algebra;
using namespace nil::crypto3::math;

typedef fields::bls12<381> FieldType;

BOOST_AUTO_TEST_CASE(expression_parser_integration1) {
    std::string expr = "pow(x/2 + sqrt(x**2/4 + y**3/24), 1/3)";
    double x = 2.0, y = -1.0;

    expressions::Parser<double> parser;
    BOOST_CHECK_NO_THROW(parser.parse(expr));

    std::map<std::string, double> symbol_table;
    symbol_table.insert(std::make_pair("x", x));
    symbol_table.insert(std::make_pair("y", y));

    double result = 0;
    BOOST_CHECK_NO_THROW(result = parser.evaluate(symbol_table));

    double expected = std::pow(
        x / 2. + std::sqrt(std::pow(x, 2.) / 4. + std::pow(y, 3.) / 24.),
        1. / 3.);
    BOOST_CHECK_CLOSE_FRACTION(result, expected,
                               std::numeric_limits<double>::epsilon());
}

BOOST_AUTO_TEST_SUITE(expression_test_suite)

// BOOST_AUTO_TEST_CASE(expression_field_evaluation) {

//     expressions::lazy_expression< typename FieldType::value_type > v0, v1;

//     expressions::lazy_expression< typename FieldType::value_type >  expr;
//     expr = (v1 - v0) + v1 * 100;

//     v0.assign(100);
//     v1.assign(505);

//     typename FieldType::value_type d = ((v1 - v0) + v1 * 100).evaluate();

//     BOOST_CHECK_EQUAL((505 - 100) + 505*100, d.data);
// }

BOOST_AUTO_TEST_CASE(expression_polynom_evaluation) {

    // expressions::lazy_expression< polynomial::polynom<typename FieldType::value_type> > v0, v1;

    // using expr_type = typename boost::proto::terminal<polynomial::polynom<typename FieldType::value_type>>::type;

    // expressions::lazy_expression< polynomial::polynom<typename FieldType::value_type> >  expr = 
    //     expressions::lazy_expression< polynomial::polynom<typename FieldType::value_type> > (v1 + v0);

    // boost::proto::display_expr(expr);

    // v0.assign({1, 3, 4, 25, 6, 7, 7, 2});
    // v1.assign({9, 3, 11, 14, 7, 1, 5, 8});

    // polynomial::polynom<typename FieldType::value_type> c_ans = {10, 6, 15, 39, 13, 8, 12, 10};

    // polynomial::polynom<typename FieldType::value_type> d = expr.evaluate();

    // for (std::size_t i = 0; i < c_ans.size(); ++i) {
    //     BOOST_CHECK_EQUAL(c_ans[i].data, d[i].data);
    // }
}

BOOST_AUTO_TEST_SUITE_END()