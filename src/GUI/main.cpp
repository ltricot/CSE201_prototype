#include <QApplication>
#include <QCheckBox>
#include <QInputDialog>
#include <QLCDNumber>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QSlider>
#include <QString>
#include <QTime>
#include <QVBoxLayout>
#include <QWidget>
#include <random>

// create a function that wait for a duration of 10 ms in order to slow down while loops
void delay() {
    QTime dieTime = QTime::currentTime().addMSecs(10);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

// create a class info_user that will store the choices of the user
class info_user {
  public:
    // generator fill up the storage with 0
    info_user() {
        stock[0] = 51;
        stock[1] = 32;
        stock[2] = 40;
        stock[3] = 10;
        stock[4] = 9;
        stock[5] = 6;
        stock[6] = 3;
        stock[7] = 3;

        for (int i = 0; i < 8; i++) {
            info[i] = new int[stock[i]];
            for (int j = 0; j < stock[i]; j++) {
                info[i][j] = 0;
            }
        }
    }

    // the update function take the checkboxes in input and fill the storage with 0 and 1
    void update_info_user(QCheckBox **a) {
        int k = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < stock[i]; j++) {
                if (a[k]->isChecked()) {
                    info[i][j] = 1;
                } else {
                    info[i][j] = 0;
                }
                k++;
            }
        }
    }

  private:
    int **info = new int *[8];
    int stock[8];
};

int main(int argc, char *argv[]) {
    // create the application
    QApplication app(argc, argv);

    // create a first window called home that is not displayed
    QWidget *home = new QWidget;

    // create the main window, core of the application (unsued for now)
    QWidget *main = new QWidget;
    main->setWindowTitle("App name");
    main->setMinimumSize(500, 500);
    QPushButton *quit_button = new QPushButton(main);
    quit_button->setText("Quit");
    QObject::connect(quit_button, SIGNAL(clicked()), qApp, SLOT(quit()));

    // Display a message box
    int ok =
        QMessageBox::question(home, "Hello", "Welcome to our app, let's start", QMessageBox::Ok);
    // Check that the button has been clicked and manage the different cases
    if (ok == QMessageBox::Ok) {
        // Open a message box that ask if the user want to log in or sign in
        int answer = QMessageBox::question(home, "Log in", "Have you an account?",
                                           QMessageBox::Yes | QMessageBox::No);
        // First case : it is a pre-existent user
        if (answer == QMessageBox::Yes) {
            // Ask for the ID and store it in "id"
            bool ok = false;
            QString id = QInputDialog::getText(home, "Log in", "Please enter your ID",
                                               QLineEdit::Normal, QString(), &ok);

            // if the button has been clicked and that the ID is not empty (we may add if the ID is
            // in id_list ?)
            if (ok && !id.isEmpty()) {
                // display the app
                home->close();
                main->show();
            }
            // If the ID is empty
            else {
                // Display an error message in a critical box
                QMessageBox::critical(home, "Error", "ID error");
            }
        }
        // Second case : it is a new user
        else {
            // Display an information box
            QMessageBox::information(home, "Sign in",
                                     "We are going to ask you a few questions about your "
                                     "interests, please answer carefully");

            // Create an array to store user info
            info_user info;

            // Create the layout for the window home that is still hidden
            QVBoxLayout *layout = new QVBoxLayout;

            // Create the text that is going to be displayed in the window home
            QLabel *title = new QLabel(home);
            title->setText("What are you ineterested in?");
            title->setFont(QFont("Courrier", 15, QFont::Bold));

            // Create some checkboxes associated tot the topics of arXiv
            QCheckBox *physics = new QCheckBox("Physics");
            QCheckBox *maths = new QCheckBox("Mathematics");
            QCheckBox *cs = new QCheckBox("Computer Science");
            QCheckBox *bio = new QCheckBox("Quantitative Biology");
            QCheckBox *fin = new QCheckBox("Quantitative Finance");
            QCheckBox *stat = new QCheckBox("Statistics");
            QCheckBox *elec = new QCheckBox("Electrical Engineering and Systems Science");
            QCheckBox *econ = new QCheckBox("Economics");

            // Create the button to valilade
            QPushButton *validate_button = new QPushButton("Validate");

            // Give a title to the window home
            home->setWindowTitle("Interests");

            // Add all the elements to the layout (button, checkboxes and text)
            layout->addWidget(title);
            layout->addWidget(physics);
            layout->addWidget(maths);
            layout->addWidget(cs);
            layout->addWidget(bio);
            layout->addWidget(fin);
            layout->addWidget(stat);
            layout->addWidget(elec);
            layout->addWidget(econ);
            layout->addWidget(validate_button);

            // Set the layout in the window and make it appear
            home->setLayout(layout);
            home->setMinimumSize(500, 200);
            home->show();

            // Create a new window and a layout for each subject
            QWidget *precise_phy = new QWidget;
            QVBoxLayout *l_p_phy = new QVBoxLayout;
            QWidget *precise_math = new QWidget;
            QVBoxLayout *l_p_math = new QVBoxLayout;
            QWidget *precise_cs = new QWidget;
            QVBoxLayout *l_p_cs = new QVBoxLayout;
            QWidget *precise_bio = new QWidget;
            QVBoxLayout *l_p_bio = new QVBoxLayout;
            QWidget *precise_fin = new QWidget;
            QVBoxLayout *l_p_fin = new QVBoxLayout;
            QWidget *precise_stat = new QWidget;
            QVBoxLayout *l_p_stat = new QVBoxLayout;
            QWidget *precise_eess = new QWidget;
            QVBoxLayout *l_p_eess = new QVBoxLayout;
            QWidget *precise_econ = new QWidget;
            QVBoxLayout *l_p_econ = new QVBoxLayout;

            // Create a text for each subject and add it to the layout associated
            QLabel *title_phy = new QLabel();
            title_phy->setText("More precisely in physics:");
            title_phy->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_phy->addWidget(title_phy);
            QLabel *title_math = new QLabel();
            title_math->setText("More precisely in mathematics:");
            title_math->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_math->addWidget(title_math);
            QLabel *title_cs = new QLabel();
            title_cs->setText("More precisely in computer science:");
            title_cs->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_cs->addWidget(title_cs);
            QLabel *title_bio = new QLabel();
            title_bio->setText("More precisely in quantitative biology:");
            title_bio->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_bio->addWidget(title_bio);
            QLabel *title_fin = new QLabel();
            title_fin->setText("More precisely in quantitative finance:");
            title_fin->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_fin->addWidget(title_fin);
            QLabel *title_stat = new QLabel();
            title_stat->setText("More precisely in statistics:");
            title_stat->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_stat->addWidget(title_stat);
            QLabel *title_elec = new QLabel();
            title_elec->setText("More precisely in Electrical Engineering and Systems Science:");
            title_elec->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_eess->addWidget(title_elec);
            QLabel *title_econ = new QLabel();
            title_econ->setText("More precisely in economics:");
            title_econ->setFont(QFont("Courrier", 15, QFont::Bold));
            l_p_econ->addWidget(title_econ);

            // Give a title to each window and create a new button validate for each of them
            precise_phy->setWindowTitle("About your interests in physics");
            precise_math->setWindowTitle("About your interests in mathematics");
            precise_cs->setWindowTitle("About your interests in computer science");
            precise_bio->setWindowTitle("About your interests in quantitative biology");
            precise_fin->setWindowTitle("About your interests in quantitative finance");
            precise_stat->setWindowTitle("About your interests in statistics");
            precise_eess->setWindowTitle(
                "About your interests in electrical engineering and systems science");
            precise_econ->setWindowTitle("About your interests in economics");
            QPushButton *val_phy = new QPushButton;
            val_phy->setText("Validate");
            QPushButton *val_math = new QPushButton;
            val_math->setText("Validate");
            QPushButton *val_cs = new QPushButton;
            val_cs->setText("Validate");
            QPushButton *val_bio = new QPushButton;
            val_bio->setText("Validate");
            QPushButton *val_fin = new QPushButton;
            val_fin->setText("Validate");
            QPushButton *val_stat = new QPushButton;
            val_stat->setText("Validate");
            QPushButton *val_eess = new QPushButton;
            val_eess->setText("Validate");
            QPushButton *val_econ = new QPushButton;
            val_econ->setText("Validate");

            // Create all the checkboxes (don't count, there are 154) and put them in the associated
            // layout ; also add the validate buttons
            QCheckBox *checkboxes[154];
            QCheckBox *galax = new QCheckBox("Astrophysics of Galaxies");
            checkboxes[0] = galax;
            QCheckBox *cosmo = new QCheckBox("Cosmology and Nongalactic Astrophysics");
            checkboxes[1] = cosmo;
            QCheckBox *earth = new QCheckBox("Earth and Planetary Astrophysics");
            checkboxes[2] = earth;
            QCheckBox *heap = new QCheckBox("High Energy Astrophysical Phenomena");
            checkboxes[3] = heap;
            QCheckBox *instru = new QCheckBox("Instrumentation and Methods for Astrophysics");
            checkboxes[4] = instru;
            QCheckBox *solar = new QCheckBox("Solar and Stellar Astrophysics");
            checkboxes[5] = solar;
            // Astro
            {
                QLabel *astro = new QLabel();
                astro->setText("astro");
                astro->setFont(QFont("Courrier", 12, QFont::Bold));
                l_p_phy->addWidget(astro);
                l_p_phy->addWidget(galax);
                l_p_phy->addWidget(cosmo);
                l_p_phy->addWidget(earth);
                l_p_phy->addWidget(heap);
                l_p_phy->addWidget(instru);
                l_p_phy->addWidget(solar);
            }
            QCheckBox *disorder = new QCheckBox("Disordered Systems and Neural Networks");
            checkboxes[6] = disorder;
            QCheckBox *materials = new QCheckBox("Materials Science");
            checkboxes[7] = materials;
            QCheckBox *meso = new QCheckBox("Mesoscale and Nanoscale Physics");
            checkboxes[8] = meso;
            QCheckBox *o_condens = new QCheckBox("Other Condensed Matter");
            checkboxes[9] = o_condens;
            QCheckBox *quant_gases = new QCheckBox("Quantum Gases");
            checkboxes[10] = quant_gases;
            QCheckBox *soft = new QCheckBox("Soft Condensed Matter");
            checkboxes[11] = soft;
            QCheckBox *stat_mech = new QCheckBox("Statistical Mechanics");
            checkboxes[12] = stat_mech;
            QCheckBox *corr_elect = new QCheckBox("Strongly Correlated Electrons");
            checkboxes[13] = corr_elect;
            QCheckBox *supercond = new QCheckBox("Superconductivity");
            checkboxes[14] = supercond;
            // Condensed
            {
                QLabel *cond_mat = new QLabel();
                cond_mat->setText("Condensed Matter");
                cond_mat->setFont(QFont("Courrier", 12, QFont::Bold));
                l_p_phy->addWidget(cond_mat);
                l_p_phy->addWidget(disorder);
                l_p_phy->addWidget(materials);
                l_p_phy->addWidget(meso);
                l_p_phy->addWidget(o_condens);
                l_p_phy->addWidget(quant_gases);
                l_p_phy->addWidget(soft);
                l_p_phy->addWidget(stat_mech);
                l_p_phy->addWidget(corr_elect);
                l_p_phy->addWidget(supercond);
            }
            QCheckBox *adapt = new QCheckBox("Adaptation and Self-Organizing Systems");
            checkboxes[15] = adapt;
            QCheckBox *cell_auto = new QCheckBox("Cellular Automata and Lattice Gases");
            checkboxes[16] = cell_auto;
            QCheckBox *chaos = new QCheckBox("Chaotic Dynamics");
            checkboxes[17] = chaos;
            QCheckBox *solvable = new QCheckBox("Exactly Solvable and Integrable Systems");
            checkboxes[18] = solvable;
            QCheckBox *pattern_form = new QCheckBox("Pattern Formation and Solitons");
            checkboxes[19] = pattern_form;
            // Non-linear
            {
                QLabel *non_lin = new QLabel();
                non_lin->setText("Nonlinear Sciences");
                non_lin->setFont(QFont("Courrier", 12, QFont::Bold));
                l_p_phy->addWidget(non_lin);
                l_p_phy->addWidget(adapt);
                l_p_phy->addWidget(cell_auto);
                l_p_phy->addWidget(chaos);
                l_p_phy->addWidget(solvable);
                l_p_phy->addWidget(pattern_form);
            }
            QCheckBox *acce = new QCheckBox("Accelerator Physics");
            checkboxes[20] = acce;
            QCheckBox *apply = new QCheckBox("Applied Physics");
            checkboxes[21] = apply;
            QCheckBox *atmo = new QCheckBox("Atmospheric and Oceanic Physics");
            checkboxes[22] = atmo;
            QCheckBox *atomic = new QCheckBox("Atomic Physics");
            checkboxes[23] = atomic;
            QCheckBox *clusters = new QCheckBox("Atomic and Molecular Clusters");
            checkboxes[24] = clusters;
            QCheckBox *bio_phy = new QCheckBox("Biological Physics");
            checkboxes[25] = bio_phy;
            QCheckBox *chem_phy = new QCheckBox("Chemical Physics");
            checkboxes[26] = chem_phy;
            QCheckBox *class_phy = new QCheckBox("Classical Physics");
            checkboxes[27] = class_phy;
            QCheckBox *comp_phy = new QCheckBox("Computational Physics");
            checkboxes[28] = comp_phy;
            QCheckBox *data_ana = new QCheckBox("Data Analysis, Statistics and Probability");
            checkboxes[29] = data_ana;
            QCheckBox *fluid = new QCheckBox("Fluid Dynamics");
            checkboxes[30] = fluid;
            QCheckBox *gen_phy = new QCheckBox("General Physics");
            checkboxes[31] = gen_phy;
            QCheckBox *geophy = new QCheckBox("Geophysics");
            checkboxes[32] = geophy;
            QCheckBox *hist_phy = new QCheckBox("History and Philosophy of Physics");
            checkboxes[33] = hist_phy;
            QCheckBox *instru_detect = new QCheckBox("Instrumentation and Detectors");
            checkboxes[34] = instru_detect;
            QCheckBox *medic = new QCheckBox("Medical Physics");
            checkboxes[35] = medic;
            QCheckBox *optics = new QCheckBox("Optics");
            checkboxes[36] = optics;
            QCheckBox *edu = new QCheckBox("Physics Education");
            checkboxes[37] = edu;
            QCheckBox *phy_socie = new QCheckBox("Physics and Society");
            checkboxes[38] = phy_socie;
            QCheckBox *plasma = new QCheckBox("Plasma Physics");
            checkboxes[39] = plasma;
            QCheckBox *pop_phy = new QCheckBox("Popular Physics");
            checkboxes[40] = pop_phy;
            QCheckBox *space_phy = new QCheckBox("Space Physics");
            checkboxes[41] = space_phy;
            // Physics
            {
                QLabel *phys = new QLabel();
                phys->setText("Physics");
                phys->setFont(QFont("Courrier", 12, QFont::Bold));
                l_p_phy->addWidget(phys);
                l_p_phy->addWidget(acce);
                l_p_phy->addWidget(apply);
                l_p_phy->addWidget(atmo);
                l_p_phy->addWidget(atomic);
                l_p_phy->addWidget(clusters);
                l_p_phy->addWidget(bio_phy);
                l_p_phy->addWidget(chem_phy);
                l_p_phy->addWidget(class_phy);
                l_p_phy->addWidget(comp_phy);
                l_p_phy->addWidget(data_ana);
                l_p_phy->addWidget(fluid);
                l_p_phy->addWidget(gen_phy);
                l_p_phy->addWidget(geophy);
                l_p_phy->addWidget(hist_phy);
                l_p_phy->addWidget(instru_detect);
                l_p_phy->addWidget(medic);
                l_p_phy->addWidget(optics);
                l_p_phy->addWidget(edu);
                l_p_phy->addWidget(phy_socie);
                l_p_phy->addWidget(plasma);
                l_p_phy->addWidget(pop_phy);
                l_p_phy->addWidget(space_phy);
            }
            QCheckBox *gen_rela = new QCheckBox("General Relativity and Quantum Cosmology");
            checkboxes[42] = gen_rela;
            QCheckBox *hep_exp = new QCheckBox("High Energy Physics - Experiment");
            checkboxes[43] = hep_exp;
            QCheckBox *hep_lat = new QCheckBox("High Energy Physics - Lattice");
            checkboxes[44] = hep_lat;
            QCheckBox *hep_pheno = new QCheckBox("High Energy Physics - Phenomenology");
            checkboxes[45] = hep_pheno;
            QCheckBox *hep_theo = new QCheckBox("High Energy Physics - Theory");
            checkboxes[46] = hep_theo;
            QCheckBox *phy_math = new QCheckBox("Mathematical Physics");
            checkboxes[47] = phy_math;
            QCheckBox *nucl_exp = new QCheckBox("Nuclear Experiment");
            checkboxes[48] = nucl_exp;
            QCheckBox *nucl_theo = new QCheckBox("Nuclear Theory");
            checkboxes[49] = nucl_theo;
            QCheckBox *quant_phy = new QCheckBox("Quantum Physics");
            checkboxes[50] = quant_phy;
            // Others
            {
                QLabel *ot = new QLabel();
                ot->setText("Other");
                ot->setFont(QFont("Courrier", 12, QFont::Bold));
                l_p_phy->addWidget(ot);
                l_p_phy->addWidget(gen_rela);
                l_p_phy->addWidget(hep_exp);
                l_p_phy->addWidget(hep_lat);
                l_p_phy->addWidget(hep_pheno);
                l_p_phy->addWidget(hep_theo);
                l_p_phy->addWidget(phy_math);
                l_p_phy->addWidget(nucl_exp);
                l_p_phy->addWidget(nucl_theo);
                l_p_phy->addWidget(quant_phy);
                l_p_phy->addWidget(val_phy);
            }
            QCheckBox *alge_geo = new QCheckBox("Algebraic Geometry");
            checkboxes[51] = alge_geo;
            QCheckBox *alge_topo = new QCheckBox("Algebraic Topology");
            checkboxes[52] = alge_topo;
            QCheckBox *pde = new QCheckBox("Analysis of PDEs");
            checkboxes[53] = pde;
            QCheckBox *categ_theo = new QCheckBox("Category Theory");
            checkboxes[54] = categ_theo;
            QCheckBox *ode = new QCheckBox("Classical Analysis and ODEs");
            checkboxes[55] = ode;
            QCheckBox *combi = new QCheckBox("Combinatorics");
            checkboxes[56] = combi;
            QCheckBox *commut = new QCheckBox("Commutative Algebra");
            checkboxes[57] = commut;
            QCheckBox *complex_var = new QCheckBox("Complex Variables");
            checkboxes[58] = complex_var;
            QCheckBox *diff_geo = new QCheckBox("Differential Geometry");
            checkboxes[59] = diff_geo;
            QCheckBox *dyn_syst = new QCheckBox("Dynamical Systems");
            checkboxes[60] = dyn_syst;
            QCheckBox *func_anal = new QCheckBox("Functional Analysis");
            checkboxes[61] = func_anal;
            QCheckBox *gen_math = new QCheckBox("General Mathematics");
            checkboxes[62] = gen_math;
            QCheckBox *gen_topo = new QCheckBox("General Topology");
            checkboxes[63] = gen_topo;
            QCheckBox *geo_topo = new QCheckBox("Geometric Topology");
            checkboxes[64] = geo_topo;
            QCheckBox *group_theo = new QCheckBox("Group Theory");
            checkboxes[65] = group_theo;
            QCheckBox *hist = new QCheckBox("History and Overview");
            checkboxes[66] = hist;
            QCheckBox *info_theo_math = new QCheckBox("Information Theory");
            checkboxes[67] = info_theo_math;
            QCheckBox *k_theo = new QCheckBox("K-Theory and Homology");
            checkboxes[68] = k_theo;
            QCheckBox *logic_math = new QCheckBox("Logic");
            checkboxes[69] = logic_math;
            QCheckBox *math_phy = new QCheckBox("Mathematical Physics");
            checkboxes[70] = math_phy;
            QCheckBox *metric_geo = new QCheckBox("Metric Geometry");
            checkboxes[71] = metric_geo;
            QCheckBox *num_theo = new QCheckBox("Number Theory");
            checkboxes[72] = num_theo;
            QCheckBox *num_ana = new QCheckBox("Numerical Analysis");
            checkboxes[73] = num_ana;
            QCheckBox *op_alg = new QCheckBox("Operator Algebras");
            checkboxes[74] = op_alg;
            QCheckBox *opti = new QCheckBox("Optimization and Control");
            checkboxes[75] = opti;
            QCheckBox *proba = new QCheckBox("Probability");
            checkboxes[76] = proba;
            QCheckBox *quantum_alg = new QCheckBox("Quantum Algebra");
            checkboxes[77] = quantum_alg;
            QCheckBox *repr_theo = new QCheckBox("Representation Theory");
            checkboxes[78] = repr_theo;
            QCheckBox *ring = new QCheckBox("Rings and Algebras");
            checkboxes[79] = ring;
            QCheckBox *spec = new QCheckBox("Spectral Theory");
            checkboxes[80] = spec;
            QCheckBox *stat_theo_math = new QCheckBox("Statistics Theory");
            checkboxes[81] = stat_theo_math;
            QCheckBox *sympletic = new QCheckBox("Symplectic Geometry");
            checkboxes[82] = sympletic;
            // maths
            {
                l_p_math->addWidget(alge_geo);
                l_p_math->addWidget(alge_topo);
                l_p_math->addWidget(pde);
                l_p_math->addWidget(categ_theo);
                l_p_math->addWidget(ode);
                l_p_math->addWidget(combi);
                l_p_math->addWidget(commut);
                l_p_math->addWidget(complex_var);
                l_p_math->addWidget(diff_geo);
                l_p_math->addWidget(dyn_syst);
                l_p_math->addWidget(func_anal);
                l_p_math->addWidget(gen_math);
                l_p_math->addWidget(gen_topo);
                l_p_math->addWidget(geo_topo);
                l_p_math->addWidget(group_theo);
                l_p_math->addWidget(hist);
                l_p_math->addWidget(info_theo_math);
                l_p_math->addWidget(k_theo);
                l_p_math->addWidget(logic_math);
                l_p_math->addWidget(math_phy);
                l_p_math->addWidget(metric_geo);
                l_p_math->addWidget(num_theo);
                l_p_math->addWidget(num_ana);
                l_p_math->addWidget(op_alg);
                l_p_math->addWidget(opti);
                l_p_math->addWidget(proba);
                l_p_math->addWidget(quantum_alg);
                l_p_math->addWidget(repr_theo);
                l_p_math->addWidget(ring);
                l_p_math->addWidget(spec);
                l_p_math->addWidget(stat_theo_math);
                l_p_math->addWidget(sympletic);
                l_p_math->addWidget(val_math);
            }
            QCheckBox *ai = new QCheckBox("Artificial Intelligence");
            checkboxes[83] = ai;
            QCheckBox *comp_lang = new QCheckBox("Computation and Language");
            checkboxes[84] = comp_lang;
            QCheckBox *complexity = new QCheckBox("Computational Complexity");
            checkboxes[85] = complexity;
            QCheckBox *cefs = new QCheckBox("Computational Engineering, Finance, and Science");
            checkboxes[86] = cefs;
            QCheckBox *comp_geo = new QCheckBox("Computational Geometry");
            checkboxes[87] = comp_geo;
            QCheckBox *cs_game_theo = new QCheckBox("Computer Science and Game Theory");
            checkboxes[88] = cs_game_theo;
            QCheckBox *vision_pattern = new QCheckBox("Computer Vision and Pattern Recognition");
            checkboxes[89] = vision_pattern;
            QCheckBox *comp_socie = new QCheckBox("Computers and Society");
            checkboxes[90] = comp_socie;
            QCheckBox *crypto = new QCheckBox("Cryptography and Security");
            checkboxes[91] = crypto;
            QCheckBox *data = new QCheckBox("Data Structures and Algorithms");
            checkboxes[92] = data;
            QCheckBox *databases = new QCheckBox("Databases");
            checkboxes[93] = databases;
            QCheckBox *library = new QCheckBox("Digital Libraries");
            checkboxes[94] = library;
            QCheckBox *discrete = new QCheckBox("Discrete Mathematics");
            checkboxes[95] = discrete;
            QCheckBox *dpcc = new QCheckBox("Distributed, Parallel, and Cluster Computing");
            checkboxes[96] = dpcc;
            QCheckBox *emerging = new QCheckBox("Emerging Technologies");
            checkboxes[97] = emerging;
            QCheckBox *formal_lang = new QCheckBox("Formal Languages and Automata Theory");
            checkboxes[98] = formal_lang;
            QCheckBox *gene_lit = new QCheckBox("General Literature");
            checkboxes[99] = gene_lit;
            QCheckBox *graphics = new QCheckBox("Graphics");
            checkboxes[100] = graphics;
            QCheckBox *hardware = new QCheckBox("Hardware Architecture");
            checkboxes[101] = hardware;
            QCheckBox *human_comp = new QCheckBox("Human-Computer Interaction");
            checkboxes[102] = human_comp;
            QCheckBox *info_retrie = new QCheckBox("Information Retrieval");
            checkboxes[103] = info_retrie;
            QCheckBox *info_theo_cs = new QCheckBox("Information Theory");
            checkboxes[104] = info_theo_cs;
            QCheckBox *logic_cs = new QCheckBox("Logic in Computer Science");
            checkboxes[105] = logic_cs;
            QCheckBox *mach_lear_cs = new QCheckBox("Machine Learning");
            checkboxes[106] = mach_lear_cs;
            QCheckBox *math_software_cs = new QCheckBox("Mathematical Software");
            checkboxes[107] = math_software_cs;
            QCheckBox *multiagent = new QCheckBox("Multiagent Systems");
            checkboxes[108] = multiagent;
            QCheckBox *multimedia = new QCheckBox("Multimedia");
            checkboxes[109] = multimedia;
            QCheckBox *network_int = new QCheckBox("Networking and Internet Architecture");
            checkboxes[110] = network_int;
            QCheckBox *neural_comp = new QCheckBox("Neural and Evolutionary Computing");
            checkboxes[111] = neural_comp;
            QCheckBox *num_anal = new QCheckBox("Numerical Analysis");
            checkboxes[112] = num_anal;
            QCheckBox *op_syst = new QCheckBox("Operating Systems");
            checkboxes[113] = op_syst;
            QCheckBox *o_cs = new QCheckBox("Other Computer Science");
            checkboxes[114] = o_cs;
            QCheckBox *perf = new QCheckBox("Performance");
            checkboxes[115] = perf;
            QCheckBox *programming = new QCheckBox("Programming Languages");
            checkboxes[116] = programming;
            QCheckBox *robot = new QCheckBox("Robotics");
            checkboxes[117] = robot;
            QCheckBox *social_net = new QCheckBox("Social and Information Networks");
            checkboxes[118] = social_net;
            QCheckBox *soft_engi = new QCheckBox("Software Engineering");
            checkboxes[119] = soft_engi;
            QCheckBox *sound_cs = new QCheckBox("Sound");
            checkboxes[120] = sound_cs;
            QCheckBox *symbol_cs = new QCheckBox("Symbolic Computation");
            checkboxes[121] = symbol_cs;
            QCheckBox *syst_control = new QCheckBox("Systems and Control");
            checkboxes[122] = syst_control;
            // Computer science
            {
                l_p_cs->addWidget(ai);
                l_p_cs->addWidget(comp_lang);
                l_p_cs->addWidget(complexity);
                l_p_cs->addWidget(cefs);
                l_p_cs->addWidget(comp_geo);
                l_p_cs->addWidget(cs_game_theo);
                l_p_cs->addWidget(vision_pattern);
                l_p_cs->addWidget(comp_socie);
                l_p_cs->addWidget(crypto);
                l_p_cs->addWidget(data);
                l_p_cs->addWidget(databases);
                l_p_cs->addWidget(library);
                l_p_cs->addWidget(discrete);
                l_p_cs->addWidget(dpcc);
                l_p_cs->addWidget(emerging);
                l_p_cs->addWidget(formal_lang);
                l_p_cs->addWidget(gene_lit);
                l_p_cs->addWidget(graphics);
                l_p_cs->addWidget(hardware);
                l_p_cs->addWidget(human_comp);
                l_p_cs->addWidget(info_retrie);
                l_p_cs->addWidget(info_theo_cs);
                l_p_cs->addWidget(logic_cs);
                l_p_cs->addWidget(mach_lear_cs);
                l_p_cs->addWidget(math_software_cs);
                l_p_cs->addWidget(multiagent);
                l_p_cs->addWidget(multimedia);
                l_p_cs->addWidget(network_int);
                l_p_cs->addWidget(neural_comp);
                l_p_cs->addWidget(num_anal);
                l_p_cs->addWidget(op_syst);
                l_p_cs->addWidget(o_cs);
                l_p_cs->addWidget(perf);
                l_p_cs->addWidget(programming);
                l_p_cs->addWidget(robot);
                l_p_cs->addWidget(social_net);
                l_p_cs->addWidget(soft_engi);
                l_p_cs->addWidget(sound_cs);
                l_p_cs->addWidget(symbol_cs);
                l_p_cs->addWidget(syst_control);
                l_p_cs->addWidget(val_cs);
            }
            QCheckBox *biomol = new QCheckBox("Biomolecules");
            checkboxes[123] = biomol;
            QCheckBox *cell_beha = new QCheckBox("Cell behavior");
            checkboxes[124] = cell_beha;
            QCheckBox *genom = new QCheckBox("Genomics");
            checkboxes[125] = genom;
            QCheckBox *mol_net = new QCheckBox("Molecular networks");
            checkboxes[126] = mol_net;
            QCheckBox *neuron = new QCheckBox("Neurons and cognition");
            checkboxes[127] = neuron;
            QCheckBox *o_bio = new QCheckBox("Other quantitative biology");
            checkboxes[128] = o_bio;
            QCheckBox *pop_evol = new QCheckBox("Populations and evolution");
            checkboxes[129] = pop_evol;
            QCheckBox *quant_method = new QCheckBox("Quantitative methods");
            checkboxes[130] = quant_method;
            QCheckBox *subcell = new QCheckBox("Subcellular processes");
            checkboxes[131] = subcell;
            QCheckBox *tissues = new QCheckBox("Tissues and organs");
            checkboxes[132] = tissues;
            // Bio
            {
                l_p_bio->addWidget(biomol);
                l_p_bio->addWidget(cell_beha);
                l_p_bio->addWidget(genom);
                l_p_bio->addWidget(mol_net);
                l_p_bio->addWidget(neuron);
                l_p_bio->addWidget(o_bio);
                l_p_bio->addWidget(pop_evol);
                l_p_bio->addWidget(quant_method);
                l_p_bio->addWidget(subcell);
                l_p_bio->addWidget(tissues);
                l_p_bio->addWidget(val_bio);
            }
            QCheckBox *comp_fin = new QCheckBox("Computational Finance");
            checkboxes[133] = comp_fin;
            QCheckBox *econ_fin = new QCheckBox("Economics");
            checkboxes[134] = econ_fin;
            QCheckBox *gen_fin = new QCheckBox("General finance");
            checkboxes[135] = gen_fin;
            QCheckBox *math_fin = new QCheckBox("Mathematical finance");
            checkboxes[136] = math_fin;
            QCheckBox *porto = new QCheckBox("Portofolio management");
            checkboxes[137] = porto;
            QCheckBox *price = new QCheckBox("Pricing of securities");
            checkboxes[138] = price;
            QCheckBox *risk = new QCheckBox("Risk management");
            checkboxes[139] = risk;
            QCheckBox *stat_fin = new QCheckBox("Statistical finance");
            checkboxes[140] = stat_fin;
            QCheckBox *trade = new QCheckBox("Trade and market microstructure");
            checkboxes[141] = trade;
            // Finance
            {
                l_p_fin->addWidget(comp_fin);
                l_p_fin->addWidget(econ_fin);
                l_p_fin->addWidget(gen_fin);
                l_p_fin->addWidget(math_fin);
                l_p_fin->addWidget(porto);
                l_p_fin->addWidget(price);
                l_p_fin->addWidget(risk);
                l_p_fin->addWidget(stat_fin);
                l_p_fin->addWidget(trade);
                l_p_fin->addWidget(val_fin);
            }
            QCheckBox *applications = new QCheckBox("Applications");
            checkboxes[142] = applications;
            QCheckBox *compute = new QCheckBox("Computations");
            checkboxes[143] = compute;
            QCheckBox *mach_lear_stat = new QCheckBox("Machine Learning");
            checkboxes[144] = mach_lear_stat;
            QCheckBox *method = new QCheckBox("Methodology");
            checkboxes[145] = method;
            QCheckBox *o_stat = new QCheckBox("Other statistics");
            checkboxes[146] = o_stat;
            QCheckBox *stat_theo = new QCheckBox("Statistics theory");
            checkboxes[147] = stat_theo;
            // Statistics
            {
                l_p_stat->addWidget(applications);
                l_p_stat->addWidget(compute);
                l_p_stat->addWidget(mach_lear_stat);
                l_p_stat->addWidget(method);
                l_p_stat->addWidget(o_stat);
                l_p_stat->addWidget(stat_theo);
                l_p_stat->addWidget(val_stat);
            }
            QCheckBox *audio = new QCheckBox("Audio and speech processing");
            checkboxes[148] = audio;
            QCheckBox *image = new QCheckBox("Image and video processing");
            checkboxes[149] = image;
            QCheckBox *signal = new QCheckBox("Signal processing");
            checkboxes[150] = signal;
            // EESS
            {
                l_p_eess->addWidget(audio);
                l_p_eess->addWidget(image);
                l_p_eess->addWidget(signal);
                l_p_eess->addWidget(val_eess);
            }
            QCheckBox *econometrics = new QCheckBox("Econometrics");
            checkboxes[151] = econometrics;
            QCheckBox *general_economics = new QCheckBox("General economics");
            checkboxes[152] = general_economics;
            QCheckBox *theoretical_econ = new QCheckBox("Theoretical economics");
            checkboxes[153] = theoretical_econ;
            // Economics
            {
                l_p_econ->addWidget(econometrics);
                l_p_econ->addWidget(general_economics);
                l_p_econ->addWidget(theoretical_econ);
                l_p_econ->addWidget(val_econ);
            }

            // set the layout for each window
            precise_phy->setLayout(l_p_phy);
            precise_math->setLayout(l_p_math);
            precise_cs->setLayout(l_p_cs);
            precise_bio->setLayout(l_p_bio);
            precise_fin->setLayout(l_p_fin);
            precise_stat->setLayout(l_p_stat);
            precise_eess->setLayout(l_p_eess);
            precise_econ->setLayout(l_p_econ);

            // check if the user has finished its choice
            QObject::connect(validate_button, SIGNAL(clicked()), home, SLOT(hide()));

            // Check every 10ms if the user has validated its choice and display the next windows on
            // each subject
            bool a = true;
            while (a) {
                // wait 10ms to avoid saturation
                delay();
                // if the user has done his choice
                if (home->isHidden()) {
                    a = false; // stop the while loop
                    // create a boolean for each checkbox of the main topics
                    bool t_phy = physics->isChecked();
                    bool t_math = maths->isChecked();
                    bool t_cs = cs->isChecked();
                    bool t_bio = bio->isChecked();
                    bool t_fin = fin->isChecked();
                    bool t_stat = stat->isChecked();
                    bool t_elec = elec->isChecked();
                    bool t_econ = econ->isChecked();
                    // if the user selected at least one of them
                    if (t_phy or t_math or t_cs or t_bio or t_fin or t_stat or t_elec or t_econ) {
                        // display windows for each subject in order to make rpecise chocies
                        if (t_phy) {
                            precise_phy->show();
                            while (precise_phy->isHidden() == false) {
                                delay();
                                QObject::connect(val_phy, SIGNAL(clicked()), precise_phy,
                                                 SLOT(hide()));
                                if (precise_phy->isHidden()) {
                                    t_phy = false;
                                }
                            }
                        }
                        if (t_math and not t_phy) {
                            precise_math->show();
                            while (precise_math->isHidden() == false) {
                                delay();
                                QObject::connect(val_math, SIGNAL(clicked()), precise_math,
                                                 SLOT(hide()));
                                if (precise_math->isHidden()) {
                                    t_math = false;
                                }
                            }
                        }
                        if (t_cs and not t_phy and not t_math) {
                            precise_cs->show();
                            while (precise_cs->isHidden() == false) {
                                delay();
                                QObject::connect(val_cs, SIGNAL(clicked()), precise_cs,
                                                 SLOT(hide()));
                                if (precise_cs->isHidden()) {
                                    t_cs = false;
                                }
                            }
                        }
                        if (t_bio and not t_phy and not t_math and not t_cs) {
                            precise_bio->show();
                            while (precise_bio->isHidden() == false) {
                                delay();
                                QObject::connect(val_bio, SIGNAL(clicked()), precise_bio,
                                                 SLOT(hide()));
                                if (precise_bio->isHidden()) {
                                    t_bio = false;
                                }
                            }
                        }
                        if (t_fin and not t_phy and not t_math and not t_cs and not t_bio) {
                            precise_fin->show();
                            while (precise_fin->isHidden() == false) {
                                delay();
                                QObject::connect(val_fin, SIGNAL(clicked()), precise_fin,
                                                 SLOT(hide()));
                                if (precise_fin->isHidden()) {
                                    t_fin = false;
                                }
                            }
                        }
                        if (t_stat and not t_phy and not t_math and not t_cs and not t_bio and
                            not t_fin) {
                            precise_stat->show();
                            while (precise_stat->isHidden() == false) {
                                delay();
                                QObject::connect(val_stat, SIGNAL(clicked()), precise_stat,
                                                 SLOT(hide()));
                                if (precise_stat->isHidden()) {
                                    t_stat = false;
                                }
                            }
                        }
                        if (t_elec and not t_phy and not t_math and not t_cs and not t_bio and
                            not t_fin and not t_stat) {
                            precise_eess->show();
                            while (precise_eess->isHidden() == false) {
                                delay();
                                QObject::connect(val_eess, SIGNAL(clicked()), precise_eess,
                                                 SLOT(hide()));
                                if (precise_eess->isHidden()) {
                                    t_elec = false;
                                }
                            }
                        }
                        if (t_econ and not t_phy and not t_math and not t_cs and not t_bio and
                            not t_fin and not t_stat and not t_elec) {
                            precise_econ->show();
                            while (precise_econ->isHidden() == false) {
                                delay();
                                QObject::connect(val_econ, SIGNAL(clicked()), precise_econ,
                                                 SLOT(hide()));
                                if (precise_econ->isHidden()) {
                                    t_econ = false;
                                }
                            }
                        }
                    }
                    // display an error if none has been selected
                    else {
                        int u = QMessageBox::critical(home, "Choice error",
                                                      "You have to select at least an interest",
                                                      QMessageBox::Ok);
                        if (u == QMessageBox::Ok) {
                            home->show();
                            a = true;
                        }
                    }
                    info.update_info_user(checkboxes); // update the user info
                }
            }

            // Create the window to give a new ID to the user
            QWidget *ID = new QWidget;
            QVBoxLayout *ID_layout = new QVBoxLayout;
            QLabel *text_id = new QLabel;
            text_id->setText("Here is your user ID. Please note it carefully, you will use it to "
                             "connect next time.");
            text_id->setFont(QFont("Courrier", 15));
            ID_layout->addWidget(text_id);
            QLabel *id_itself = new QLabel;
            id_itself->setText("000000000");
            id_itself->setFont(QFont("Courrier", 25, QFont::Bold));
            ID_layout->addWidget(id_itself);
            QPushButton *val_id = new QPushButton;
            val_id->setText("I have noted my ID and I continue");
            ID_layout->addWidget(val_id);
            ID->setLayout(ID_layout);
            ID->show();
            QObject::connect(val_id, SIGNAL(clicked()), ID, SLOT(hide()));

            bool b = true;
            while (b) {
                delay();
                if (ID->isHidden()) {
                    b = false;
                    ID->close();
                    home->close();
                    main->show();
                }
            }
        }
    }
    return app.exec();
}
