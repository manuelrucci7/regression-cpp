#include <Eigen/Dense>
#include <vector>
#include <string> // String functions
#include <iostream>
#include <fstream>      // std::ofstream

Eigen::MatrixXf solve_LeastSquares(Eigen::MatrixXf X, Eigen::MatrixXf Y)
{   
    // https://eigen.tuxfamily.org/dox/group__LeastSquares.html
    // Solution: Y = X*b --> b = ( (XT*X)^-1 )*XT*Y
    // X = Nx2 # 1, x
    // Y = Nx1 
    // Assumption X and Y have the same number of samples
    Eigen::MatrixXf b = (X.transpose() * X).ldlt().solve(X.transpose() * Y);
    // std::cout << "The solution using normal equations is:\n" << b << std::endl;
    return b;
}

void trajectory_smoothing(Eigen::MatrixXf X, Eigen::MatrixXf Y, int window_size, Eigen::MatrixXf &Y_hat, Eigen::MatrixXf &Wf)
{       
    // Trajectory smoothing using least square approach (normal equation solution)

    // Assumption X.rows = Y.rows
    int n = Y.rows();
    Y_hat = Eigen::MatrixXf::Zero(Y.rows(),Y.cols());
    //std::cout << "n: " << n << std::endl;
    int i = window_size;
    while(i<n)
    {
        //std::cout << "i: " << i << std::endl;
        // Get box data depending on window size
        int  n_rows = window_size;
        int start = i-window_size;
        if ((start+n_rows)>n) n_rows = n-start;
        Eigen::MatrixXf Xt = X.block(start,0, n_rows, X.cols());
        Eigen::MatrixXf Yt = Y.block(start,0, n_rows, Y.cols());
        // Solve least square
        Eigen::MatrixXf bt = solve_LeastSquares(Xt, Yt);
        // Predict
        Eigen::MatrixXf Yt_hat = Xt*bt;
        // Store data
        Y_hat.block(start,0,n_rows,Y.cols()) = Yt_hat;
        // Increment start
        i = i + window_size;


        // Sto Last weight for future prediction
        Wf = bt;
    }
}


int main(int argc, char **argv)
{
    // Params
    int win_size = 21;

    std::vector<float> x {
        0.0 ,
    0.023411371237458192 ,
    0.046822742474916385 ,
    0.07023411371237458 ,
    0.09364548494983277 ,
    0.11705685618729096 ,
    0.14046822742474915 ,
    0.16387959866220736 ,
    0.18729096989966554 ,
    0.21070234113712372 ,
    0.23411371237458192 ,
    0.25752508361204013 ,
    0.2809364548494983 ,
    0.3043478260869565 ,
    0.3277591973244147 ,
    0.3511705685618729 ,
    0.3745819397993311 ,
    0.39799331103678925 ,
    0.42140468227424743 ,
    0.44481605351170567 ,
    0.46822742474916385 ,
    0.491638795986622 ,
    0.5150501672240803 ,
    0.5384615384615384 ,
    0.5618729096989966 ,
    0.5852842809364548 ,
    0.608695652173913 ,
    0.6321070234113711 ,
    0.6555183946488294 ,
    0.6789297658862876 ,
    0.7023411371237458 ,
    0.725752508361204 ,
    0.7491638795986622 ,
    0.7725752508361203 ,
    0.7959866220735785 ,
    0.8193979933110367 ,
    0.8428093645484949 ,
    0.8662207357859532 ,
    0.8896321070234113 ,
    0.9130434782608695 ,
    0.9364548494983277 ,
    0.9598662207357859 ,
    0.983277591973244 ,
    1.0066889632107023 ,
    1.0301003344481605 ,
    1.0535117056856187 ,
    1.0769230769230769 ,
    1.100334448160535 ,
    1.1237458193979932 ,
    1.1471571906354514 ,
    1.1705685618729096 ,
    1.1939799331103678 ,
    1.217391304347826 ,
    1.2408026755852841 ,
    1.2642140468227423 ,
    1.2876254180602005 ,
    1.3110367892976589 ,
    1.334448160535117 ,
    1.3578595317725752 ,
    1.3812709030100334 ,
    1.4046822742474916 ,
    1.4280936454849498 ,
    1.451505016722408 ,
    1.4749163879598661 ,
    1.4983277591973243 ,
    1.5217391304347825 ,
    1.5451505016722407 ,
    1.5685618729096988 ,
    1.591973244147157 ,
    1.6153846153846152 ,
    1.6387959866220734 ,
    1.6622073578595316 ,
    1.6856187290969897 ,
    1.7090301003344481 ,
    1.7324414715719063 ,
    1.7558528428093645 ,
    1.7792642140468227 ,
    1.8026755852842808 ,
    1.826086956521739 ,
    1.8494983277591972 ,
    1.8729096989966554 ,
    1.8963210702341136 ,
    1.9197324414715717 ,
    1.94314381270903 ,
    1.966555183946488 ,
    1.9899665551839463 ,
    2.0133779264214047 ,
    2.0367892976588626 ,
    2.060200668896321 ,
    2.083612040133779 ,
    2.1070234113712374 ,
    2.1304347826086953 ,
    2.1538461538461537 ,
    2.1772575250836117 ,
    2.20066889632107 ,
    2.224080267558528 ,
    2.2474916387959865 ,
    2.270903010033445 ,
    2.294314381270903 ,
    2.317725752508361 ,
    2.341137123745819 ,
    2.3645484949832776 ,
    2.3879598662207355 ,
    2.411371237458194 ,
    2.434782608695652 ,
    2.4581939799331103 ,
    2.4816053511705682 ,
    2.5050167224080266 ,
    2.5284280936454846 ,
    2.551839464882943 ,
    2.575250836120401 ,
    2.5986622073578594 ,
    2.6220735785953178 ,
    2.6454849498327757 ,
    2.668896321070234 ,
    2.692307692307692 ,
    2.7157190635451505 ,
    2.7391304347826084 ,
    2.762541806020067 ,
    2.785953177257525 ,
    2.809364548494983 ,
    2.832775919732441 ,
    2.8561872909698995 ,
    2.8795986622073575 ,
    2.903010033444816 ,
    2.926421404682274 ,
    2.9498327759197323 ,
    2.97324414715719 ,
    2.9966555183946486 ,
    3.020066889632107 ,
    3.043478260869565 ,
    3.0668896321070234 ,
    3.0903010033444813 ,
    3.1137123745819397 ,
    3.1371237458193977 ,
    3.160535117056856 ,
    3.183946488294314 ,
    3.2073578595317724 ,
    3.2307692307692304 ,
    3.254180602006689 ,
    3.2775919732441468 ,
    3.301003344481605 ,
    3.324414715719063 ,
    3.3478260869565215 ,
    3.3712374581939795 ,
    3.394648829431438 ,
    3.4180602006688963 ,
    3.441471571906354 ,
    3.4648829431438126 ,
    3.4882943143812706 ,
    3.511705685618729 ,
    3.535117056856187 ,
    3.5585284280936453 ,
    3.5819397993311033 ,
    3.6053511705685617 ,
    3.6287625418060196 ,
    3.652173913043478 ,
    3.675585284280936 ,
    3.6989966555183944 ,
    3.7224080267558524 ,
    3.7458193979933108 ,
    3.769230769230769 ,
    3.792642140468227 ,
    3.8160535117056855 ,
    3.8394648829431435 ,
    3.862876254180602 ,
    3.88628762541806 ,
    3.9096989966555182 ,
    3.933110367892976 ,
    3.9565217391304346 ,
    3.9799331103678925 ,
    4.0033444816053505 ,
    4.026755852842809 ,
    4.050167224080267 ,
    4.073578595317725 ,
    4.096989966555183 ,
    4.120401337792642 ,
    4.1438127090301 ,
    4.167224080267558 ,
    4.190635451505017 ,
    4.214046822742475 ,
    4.237458193979933 ,
    4.260869565217391 ,
    4.2842809364548495 ,
    4.3076923076923075 ,
    4.331103678929765 ,
    4.354515050167223 ,
    4.377926421404682 ,
    4.40133779264214 ,
    4.424749163879598 ,
    4.448160535117056 ,
    4.471571906354515 ,
    4.494983277591973 ,
    4.518394648829431 ,
    4.54180602006689 ,
    4.565217391304348 ,
    4.588628762541806 ,
    4.612040133779264 ,
    4.635451505016722 ,
    4.65886287625418 ,
    4.682274247491638 ,
    4.705685618729096 ,
    4.729096989966555 ,
    4.752508361204013 ,
    4.775919732441471 ,
    4.799331103678929 ,
    4.822742474916388 ,
    4.846153846153846 ,
    4.869565217391304 ,
    4.892976588628763 ,
    4.916387959866221 ,
    4.9397993311036785 ,
    4.9632107023411365 ,
    4.986622073578595 ,
    5.010033444816053 ,
    5.033444816053511 ,
    5.056856187290969 ,
    5.080267558528428 ,
    5.103678929765886 ,
    5.127090301003344 ,
    5.150501672240802 ,
    5.173913043478261 ,
    5.197324414715719 ,
    5.220735785953177 ,
    5.2441471571906355 ,
    5.2675585284280935 ,
    5.290969899665551 ,
    5.314381270903009 ,
    5.337792642140468 ,
    5.361204013377926 ,
    5.384615384615384 ,
    5.408026755852842 ,
    5.431438127090301 ,
    5.454849498327759 ,
    5.478260869565217 ,
    5.501672240802675 ,
    5.525083612040134 ,
    5.548494983277592 ,
    5.57190635451505 ,
    5.5953177257525075 ,
    5.618729096989966 ,
    5.642140468227424 ,
    5.665551839464882 ,
    5.688963210702341 ,
    5.712374581939799 ,
    5.735785953177257 ,
    5.759197324414715 ,
    5.782608695652174 ,
    5.806020066889632 ,
    5.82943143812709 ,
    5.852842809364548 ,
    5.8762541806020065 ,
    5.8996655518394645 ,
    5.9230769230769225 ,
    5.94648829431438 ,
    5.969899665551839 ,
    5.993311036789297 ,
    6.016722408026755 ,
    6.040133779264214 ,
    6.063545150501672 ,
    6.08695652173913 ,
    6.110367892976588 ,
    6.133779264214047 ,
    6.157190635451505 ,
    6.180602006688963 ,
    6.204013377926421 ,
    6.2274247491638794 ,
    6.250836120401337 ,
    6.274247491638795 ,
    6.297658862876253 ,
    6.321070234113712 ,
    6.34448160535117 ,
    6.367892976588628 ,
    6.391304347826087 ,
    6.414715719063545 ,
    6.438127090301003 ,
    6.461538461538461 ,
    6.48494983277592 ,
    6.508361204013378 ,
    6.5317725752508355 ,
    6.5551839464882935 ,
    6.578595317725752 ,
    6.60200668896321 ,
    6.625418060200668 ,
    6.648829431438126 ,
    6.672240802675585 ,
    6.695652173913043 ,
    6.719063545150501 ,
    6.742474916387959 ,
    6.765886287625418 ,
    6.789297658862876 ,
    6.812709030100334 ,
    6.8361204013377925 ,
    6.8595317725752505 ,
    6.882943143812708 ,
    6.906354515050166 ,
    6.929765886287625 ,
    6.953177257525083 ,
    6.976588628762541 ,
    7.0 
};

    std::vector<float> y {
        0.0 ,
    0.022867555899094543 ,
    0.044664583456276455 ,
    0.06541671166867687 ,
    0.08514951607280126 ,
    0.1038884938032208 ,
    0.12165903987611985 ,
    0.1384864246670668 ,
    0.1543957725524971 ,
    0.16941204168454801 ,
    0.1835600048690585 ,
    0.1968642315167483 ,
    0.20934907063781183 ,
    0.2210386348504082 ,
    0.23195678537379089 ,
    0.24212711797710657 ,
    0.25157294985519446 ,
    0.26031730740303416 ,
    0.2683829148608271 ,
    0.27579218380204473 ,
    0.2825672034371392 ,
    0.28872973170598876 ,
    0.29430118713253633 ,
    0.2993026414154788 ,
    0.3037548127292705 ,
    0.3076780597101235 ,
    0.31109237610210877 ,
    0.3140173860388972 ,
    0.3164723399371168 ,
    0.3184761109777444 ,
    0.3200471921524029 ,
    0.3212036938518845 ,
    0.3219633419746805 ,
    0.32234347653375484 ,
    0.32236105074026217 ,
    0.32203263054337566 ,
    0.32137439460585143 ,
    0.32040213469542483 ,
    0.3191312564725983 ,
    0.31757678065584305 ,
    0.3157533445457048 ,
    0.31367520388976267 ,
    0.31135623507085264 ,
    0.30880993760142533 ,
    0.30604943690736347 ,
    0.3030874873850369 ,
    0.29993647571582316 ,
    0.2966084244227664 ,
    0.2931149956544907 ,
    0.28946749518191955 ,
    0.28567687659378826 ,
    0.28175374567736194 ,
    0.27770836497119766 ,
    0.273550658477204 ,
    0.2692902165196671 ,
    0.26493630073931596 ,
    0.2604978492109028 ,
    0.25598348167316876 ,
    0.25140150486045215 ,
    0.24675991792558272 ,
    0.24206641794407793 ,
    0.23732840549002795 ,
    0.2325529902744207 ,
    0.22774699683701147 ,
    0.22291697028319404 ,
    0.21806918205767106 ,
    0.21320963574705792 ,
    0.2083440729038831 ,
    0.2034779788847696 ,
    0.1986165886958974 ,
    0.19376489283915452 ,
    0.18892764315268432 ,
    0.1841093586398322 ,
    0.17931433128077978 ,
    0.17454663182143598 ,
    0.16981011553442546 ,
    0.16510842794728306 ,
    0.1604450105332198 ,
    0.15582310636007862 ,
    0.1512457656933438 ,
    0.1467158515493057 ,
    0.14223604519471483 ,
    0.13780885158948325 ,
    0.13343660476921104 ,
    0.1291214731645263 ,
    0.12486546485443309 ,
    0.12067043275106062 ,
    0.11653807971340024 ,
    0.11246996358780106 ,
    0.10846750217317969 ,
    0.10453197810906809 ,
    0.10066454368479784 ,
    0.09686622556827586 ,
    0.09313792945296864 ,
    0.08948044462185796 ,
    0.08589444842728111 ,
    0.08238051068570414 ,
    0.07893909798661553 ,
    0.07557057791485271 ,
    0.07227522318580108 ,
    0.06905321569302324 ,
    0.06590465046798848 ,
    0.06282953955168509 ,
    0.05982781577799867 ,
    0.05689933646884287 ,
    0.054043887041120994 ,
    0.05126118452569072 ,
    0.048550880998587426 ,
    0.0459125669248473 ,
    0.04334577441534566 ,
    0.040849980397143895 ,
    0.038424609697904843 ,
    0.03606903804500599 ,
    0.03378259498004004 ,
    0.03156456668945266 ,
    0.029414198752123016 ,
    0.027330698804743297 ,
    0.02531323912590427 ,
    0.023360959139837413 ,
    0.021472967840808852 ,
    0.019648346139197546 ,
    0.01788614913032906 ,
    0.0161854082871677 ,
    0.014545133578003156 ,
    0.0129643155102939 ,
    0.011441927101857647 ,
    0.00997692578062048 ,
    0.008568255214159309 ,
    0.007214847070289079 ,
    0.005915622709964647 ,
    0.004669494813779925 ,
    0.0034753689433604604 ,
    0.002332145038955844 ,
    0.0012387188545461977 ,
    0.00019398333178499282 ,
    -0.0008031700858958732 ,
    -0.0017538501976880846 ,
    -0.002659164846984819 ,
    -0.003520219778801838 ,
    -0.004338117551711364 ,
    -0.005113956502959711 ,
    -0.005848829765444558 ,
    -0.006543824335231773 ,
    -0.007200020188298908 ,
    -0.007818489445198955 ,
    -0.008400295582347209 ,
    -0.008946492688642753 ,
    -0.00945812476614709 ,
    -0.009936225073553349 ,
    -0.010381815511191593 ,
    -0.010795906046329014 ,
    -0.011179494177536903 ,
    -0.011533564436911198 ,
    -0.011859087928947805 ,
    -0.012157021904890028 ,
    -0.012428309371381044 ,
    -0.012673878732271457 ,
    -0.012894643462448695 ,
    -0.01309150181257288 ,
    -0.013265336543621439 ,
    -0.013417014690163256 ,
    -0.01354738735130163 ,
    -0.013657289508244201 ,
    -0.013747539867477272 ,
    -0.01381894072854112 ,
    -0.01387227787542262 ,
    -0.013908320490601138 ,
    -0.01392782109080345 ,
    -0.013931515483543494 ,
    -0.013920122743542684 ,
    -0.013894345208146643 ,
    -0.013854868490874285 ,
    -0.013802361512255347 ,
    -0.01373747654713246 ,
    -0.013660849287623967 ,
    -0.013573098920963764 ,
    -0.013474828221454167 ,
    -0.01336662365578788 ,
    -0.013249055501014616 ,
    -0.013122677974447756 ,
    -0.012988029374825684 ,
    -0.012845632234061814 ,
    -0.012695993478936502 ,
    -0.012539604602102869 ,
    -0.01237694184179741 ,
    -0.012208466369664698 ,
    -0.012034624486123986 ,
    -0.011855847822723423 ,
    -0.011672553550945661 ,
    -0.011485144596945978 ,
    -0.01129400986172182 ,
    -0.011099524446229376 ,
    -0.010902049880979935 ,
    -0.010701934359665141 ,
    -0.010499512976376805 ,
    -0.010295107966002767 ,
    -0.010089028947396047 ,
    -0.00988157316893015 ,
    -0.00967302575606834 ,
    -0.009463659960589723 ,
    -0.00925373741112936 ,
    -0.009043508364704182 ,
    -0.008833211958910125 ,
    -0.008623076464489851 ,
    -0.008413319537983494 ,
    -0.00820414847418825 ,
    -0.007995760458165134 ,
    -0.007788342816543774 ,
    -0.007582073267888218 ,
    -0.007377120171898683 ,
    -0.007173642777235634 ,
    -0.006971791467763712 ,
    -0.006771708007024303 ,
    -0.006573525780755841 ,
    -0.0063773700372915494 ,
    -0.00618335812567418 ,
    -0.005991599731337342 ,
    -0.005802197109212242 ,
    -0.005615245314128098 ,
    -0.005430832428383163 ,
    -0.0052490397863722655 ,
    -0.005069942196164836 ,
    -0.004893608157935764 ,
    -0.0047201000791590045 ,
    -0.004549474486481727 ,
    -0.004381782234203917 ,
    -0.004217068709295391 ,
    -0.004055374032889218 ,
    -0.0038967332581968466 ,
    -0.0037411765647967824 ,
    -0.0035887294492545447 ,
    -0.003439412912037723 ,
    -0.0032932436406953726 ,
    -0.0031502341892765337 ,
    -0.0030103931539677037 ,
    -0.0028737253449342593 ,
    -0.002740231954355356 ,
    -0.0026099107206465854 ,
    -0.0024827560888688134 ,
    -0.0023587593673260045 ,
    -0.002237908880358592 ,
    -0.002120190117342858 ,
    -0.002005585877910262 ,
    -0.0018940764134041967 ,
    -0.001785639564594784 ,
    -0.0016802508956753673 ,
    -0.0015778838245673827 ,
    -0.00147850974956288 ,
    -0.0013820981723366584 ,
    -0.0012886168173622942 ,
    -0.0011980317477687686 ,
    -0.001110307477676386 ,
    -0.001025407081052788 ,
    -0.000943292297131629 ,
    -0.0008639236324383221 ,
    -0.0007872604594687697 ,
    -0.0007132611120685381 ,
    -0.0006418829775612419 ,
    -0.0005730825856762326 ,
    -0.0005068156943267567 ,
    -0.0004430373722907743 ,
    -0.000381702078847636 ,
    -0.00032276374042455 ,
    -0.0002661758243075763 ,
    -0.0002118914094724589 ,
    -0.0001598632545912433 ,
    -0.0001100438632710092 ,
    -6.238554658149788e-05 ,
    -1.684048292866289e-05 ,
    2.6639224668525466e-05 ,
    6.810149384060027e-05 ,
    0.00010759421061187894 ,
    0.00014516517956896188 ,
    0.0001808620763958879 ,
    0.0002147324027185287 ,
    0.0002468234432009538 ,
    0.00027718222483667077 ,
    0.00030585547837795065 ,
    0.00033288960184672497 ,
    0.0003583306260709256 ,
    0.00038222418219049876 ,
    0.0004046154710778083 ,
    0.0004255492346175877 ,
    0.00044506972879214857 ,
    0.00046322069851807154 ,
    0.000480045354181216 ,
    0.0004955863498174838 ,
    0.000509885762887426 ,
    0.0005229850755934317 ,
    0.0005349251576889509 ,
    0.0005457462507299018 ,
    0.0005554879537191656 ,
    0.0005641892100958047 ,
    0.0005718882960214303 ,
    0.0005786228099169304 ,
    0.0005844296632035557 ,
    0.0005893450722031986 ,
    0.0005934045511535032 ,
    0.000596642906294297 ,
    0.0005990942309826656 ,
    };

    // Get number of data
    int num = x.size();

    // Equation
    // y = w0*x0 + w1*x1 + w2*x2 
    // x0 = 1
    // x1 = x
    // x2 = x**2
    


    // -----------------------------------------------------------------
    // Preparation
    Eigen::MatrixXf X = Eigen::MatrixXf::Ones(num,3); // 1 x x^2 x*3 #  --Grado 2 -->3 , Grado 3 --> 4 Grado 1 -->2
    Eigen::MatrixXf Y = Eigen::MatrixXf::Zero(num,1);
    
    for (int i=0; i< num; i++)
    {
        // Polynomial feature approach 
        X(i,1) = x[i];                // x1
        X(i,2) = std::pow(x[i],2);    // x2
        //X(i,3) = std::pow(x[i],3);    // x2
        Y(i,0) = y[i];             // y
    }
    
    Eigen::MatrixXf Y_hat = Eigen::MatrixXf::Zero(num,1);
    Eigen::MatrixXf Wf;
    trajectory_smoothing( X,  Y, win_size, Y_hat, Wf );

    // Store su file resutls
    std::ofstream ofs ("res.csv", std::ofstream::out);
    ofs << "x" << ",y" << ",y_hat" << std::endl;
    for (int i=0; i< num; i++)
    {
        // Polynomial feature approach 
        ofs << x[i] << "," << y[i] << "," << Y_hat(i,0) << std::endl;
    }
    ofs.close();





    // -----------------------------------------------------------------
    //  ----- Predict Future data
    std::vector<float> x_future {
        7.0,
        7.1,
        7.4,
        8.1
    };
    Eigen::MatrixXf X_future = Eigen::MatrixXf::Ones(x_future.size(),3); // 1 x x^2 x*3 #  --Grado 2 -->3 , Grado 3 --> 4 Grado 1 -->2
    Eigen::MatrixXf Y_hat_future = Eigen::MatrixXf::Ones(x_future.size(),1); // 1 x x^2 x*3 #  --Grado 2 -->3 , Grado 3 --> 4 Grado 1 -->2
    
    for (int i=0; i< x_future.size(); i++)
    {
        // Polynomial feature approach 
        X_future(i,1) = x_future[i];                 // x1
        X_future(i,2) = std::pow(x_future[i],2);     // x2
        //X_future(i,3) = std::pow(x_future[i],3);   // x2
    }

    // Prediciton
    Y_hat_future = X_future*Wf;

    for (int i=0; i< x_future.size(); i++)
    {
        // Polynomial feature approach 
        std::cout << "X: " << X_future(i,1) << " Y_hat: " <<  Y_hat_future(i,0) <<  std::endl;
    }

    // Print prediciton weight
    // y = w0 + w1*x1 + w2*x2 
    std::cout << "Equation: Poly deg=2  y= w0 + w1*x1 + w2*x2 "  << std::endl;
    for (int i=0; i< Wf.size(); i++)
    {
        // Polynomial feature approach 
        std::cout << "w" << i << " " << Wf(i,0)  << std::endl;
    }
 
    return 0;
}