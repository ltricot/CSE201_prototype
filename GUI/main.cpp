#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QProgressBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QProcess>
#include <QString>
#include <QInputDialog>
#include <QCheckBox>
#include <QLabel>
#include <QTime>
#include <QScrollBar>
#include <QScrollArea>

// create a function that wait for a duration of 10 ms in order to slow down while loops
void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(10);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

class info_user{
    public:
        info_user()
        {
            stock[0] = 51;
            stock[1] = 32;
            stock[2] = 40;
            stock[3] = 10;
            stock[4] = 9;
            stock[5] = 6;
            stock[6] = 3;
            stock[7] = 3;

            for (int i = 0; i < 8; i++)
            {
                info[i] = new int[stock[i]];
                for (int j = 0; j < stock[i]; j++)
                {
                    info[i][j] = 0;
                }
            }


        }

        void update_info_user(QCheckBox** a)
        {
            int k = 0;
            for(int i = 0; i < 8; i ++)
            {
                for(int j = 0; j < stock[i]; j++)
                {
                    info[i][j] = a[k]->isChecked();
                    k ++;
                }
            }
        }

    private:
        int** info = new int*[8];
        int stock[8];
};

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        QWidget* widget;
        if (  (deleteWidgets)
              && (widget = item->widget())  ) {
            delete widget;
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

int main(int argc, char *argv[])
{
    // create the application
    QApplication app(argc, argv);

    // create a first window called home that is not displayed
    QWidget *home = new QWidget;

    // Display a message box
    int ok = QMessageBox::question(home, "Hello", "Welcome to our app, let's start", QMessageBox::Ok);
    // Check that the button has been clicked
    if (ok == QMessageBox::Ok)
    {
        // Open a message box that ask if the user want to log in or sign in
        int answer = QMessageBox::question(home, "Log in", "Have you an account?", QMessageBox::Yes | QMessageBox::No);
        // First case : it is a pre-existent user
        if (answer == QMessageBox::Yes)
        {
            // Ask for the ID and store it in "id"
            bool ok = false;
            QString id = QInputDialog::getText(home, "Log in", "Please enter your ID", QLineEdit::Normal, QString(), &ok);

            // if the button has been clicked and that the ID is not empty (we may add if the ID is in id_list ?)
            if (ok && !id.isEmpty())
            {
                   // IT HAS NOT BEEN CODED YET
            }
            // If the ID is empty
            else
            {
                // Display an error message in a critical box
                QMessageBox::critical(home, "Error", "ID error");
            }
        }
        // Second case : it is a new user
        else
        {
            // Display an information box
            QMessageBox::information(home, "Sign in", "We are going to ask you a few questions about your interests, please answer carefully");

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

            // Create a boolean (see use after)
            bool a = true;

            // Create a new window, set its minimum size
            QWidget *precise = new QWidget;

            // Create a text for each subject
            QLabel *title_phy = new QLabel();
            title_phy->setText("More precisely in physics:");
            title_phy->setFont(QFont("Courrier", 15, QFont::Bold));
            QLabel *title_math = new QLabel();
            title_math->setText("More precisely in mathematics:");
            title_math->setFont(QFont("Courrier", 15, QFont::Bold));
            QLabel *title_cs = new QLabel();
            title_cs->setText("More precisely in computer science:");
            title_cs->setFont(QFont("Courrier", 15, QFont::Bold));
            QLabel *title_bio = new QLabel();
            title_bio->setText("More precisely in quantitative biology:");
            title_bio->setFont(QFont("Courrier", 15, QFont::Bold));
            QLabel *title_fin = new QLabel();
            title_fin->setText("More precisely in quantitative finance:");
            title_fin->setFont(QFont("Courrier", 15, QFont::Bold));
            QLabel *title_stat = new QLabel();
            title_stat->setText("More precisely in statistics:");
            title_stat->setFont(QFont("Courrier", 15, QFont::Bold));
            QLabel *title_elec = new QLabel();
            title_elec->setText("More precisely in Electrical Engineering and Systems Science:");
            title_elec->setFont(QFont("Courrier", 15, QFont::Bold));
            QLabel *title_econ = new QLabel();
            title_econ->setText("More precisely in economics:");
            title_econ->setFont(QFont("Courrier", 15, QFont::Bold));

            // Give a title to the window and create a new button
            precise->setWindowTitle("About your interests");
            QPushButton *val = new QPushButton;
            val->setText("Validate");

            // Create all the checkboxes (don't count, there are 154)
            QCheckBox *checkboxes[154];
            QCheckBox *galax = new QCheckBox("Astrophysics of Galaxies");
            checkboxes[0]=galax;
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
            QCheckBox *audio = new QCheckBox("Audio and speech processing");
            checkboxes[148] = audio;
            QCheckBox *image = new QCheckBox("Image and video processing");
            checkboxes[149] = image;
            QCheckBox *signal = new QCheckBox("Signal processing");
            checkboxes[150] = signal;
            QCheckBox *econometrics = new QCheckBox("Econometrics");
            checkboxes[151] = econometrics;
            QCheckBox *general_economics = new QCheckBox("General economics");
            checkboxes[152] = general_economics;
            QCheckBox *theoretical_econ = new QCheckBox("Theoretical economics");
            checkboxes[153] = theoretical_econ;

            QVBoxLayout *layout2 = new QVBoxLayout;

            // Check every 10ms if the user has validated its choice
            while (a)
            {
                // Clear the layout for the second window
                // Check for each subject. If a subject has been selected
                if (physics->isChecked())
                {
                    physics->setDisabled(true);
                    layout2->addWidget(title_phy);

                    //Astro
                    {
                    QLabel *astro = new QLabel();
                    astro->setText("astro");
                    astro->setFont(QFont("Courrier", 12, QFont::Bold));
                    layout2->addWidget(astro);
                    layout2->addWidget(galax);
                    layout2->addWidget(cosmo);
                    layout2->addWidget(earth);
                    layout2->addWidget(heap);
                    layout2->addWidget(instru);
                    layout2->addWidget(solar);
                    }
                    //Condensed
                    {
                    QLabel *cond_mat = new QLabel();
                    cond_mat->setText("Condensed Matter");
                    cond_mat->setFont(QFont("Courrier", 12, QFont::Bold));
                    layout2->addWidget(cond_mat);
                    layout2->addWidget(disorder);
                    layout2->addWidget(materials);
                    layout2->addWidget(meso);
                    layout2->addWidget(o_condens);
                    layout2->addWidget(quant_gases);
                    layout2->addWidget(soft);
                    layout2->addWidget(stat_mech);
                    layout2->addWidget(corr_elect);
                    layout2->addWidget(supercond);
                    }
                    //Non-linear
                    {
                    QLabel *non_lin = new QLabel();
                    non_lin->setText("Nonlinear Sciences");
                    non_lin->setFont(QFont("Courrier", 12, QFont::Bold));
                    layout2->addWidget(non_lin);
                    layout2->addWidget(adapt);
                    layout2->addWidget(cell_auto);
                    layout2->addWidget(chaos);
                    layout2->addWidget(solvable);
                    layout2->addWidget(pattern_form);
                    }
                    //Physics
                    {
                    QLabel *phys = new QLabel();
                    phys->setText("Physics");
                    phys->setFont(QFont("Courrier", 12, QFont::Bold));
                    layout2->addWidget(phys);
                    layout2->addWidget(acce);
                    layout2->addWidget(apply);
                    layout2->addWidget(atmo);
                    layout2->addWidget(atomic);
                    layout2->addWidget(clusters);
                    layout2->addWidget(bio_phy);
                    layout2->addWidget(chem_phy);
                    layout2->addWidget(class_phy);
                    layout2->addWidget(comp_phy);
                    layout2->addWidget(data_ana);
                    layout2->addWidget(fluid);
                    layout2->addWidget(gen_phy);
                    layout2->addWidget(geophy);
                    layout2->addWidget(hist_phy);
                    layout2->addWidget(instru_detect);
                    layout2->addWidget(medic);
                    layout2->addWidget(optics);
                    layout2->addWidget(edu);
                    layout2->addWidget(phy_socie);
                    layout2->addWidget(plasma);
                    layout2->addWidget(pop_phy);
                    layout2->addWidget(space_phy);
                    }
                    //Others
                    {
                    QLabel *ot = new QLabel();
                    ot->setText("Other");
                    ot->setFont(QFont("Courrier", 12, QFont::Bold));
                    layout2->addWidget(ot);
                    layout2->addWidget(gen_rela);
                    layout2->addWidget(hep_exp);
                    layout2->addWidget(hep_lat);
                    layout2->addWidget(hep_pheno);
                    layout2->addWidget(hep_theo);
                    layout2->addWidget(phy_math);
                    layout2->addWidget(nucl_exp);
                    layout2->addWidget(nucl_theo);
                    layout2->addWidget(quant_phy);
                    }
                }
                if(maths->isChecked())
                {
                    maths->setDisabled(true);
                    layout2->addWidget(title_math);
                    layout2->addWidget(alge_geo);
                    layout2->addWidget(alge_topo);
                    layout2->addWidget(pde);
                    layout2->addWidget(categ_theo);
                    layout2->addWidget(ode);
                    layout2->addWidget(combi);
                    layout2->addWidget(commut);
                    layout2->addWidget(complex_var);
                    layout2->addWidget(diff_geo);
                    layout2->addWidget(dyn_syst);
                    layout2->addWidget(func_anal);
                    layout2->addWidget(gen_math);
                    layout2->addWidget(gen_topo);
                    layout2->addWidget(geo_topo);
                    layout2->addWidget(group_theo);
                    layout2->addWidget(hist);
                    layout2->addWidget(info_theo_math);
                    layout2->addWidget(k_theo);
                    layout2->addWidget(logic_math);
                    layout2->addWidget(math_phy);
                    layout2->addWidget(metric_geo);
                    layout2->addWidget(num_theo);
                    layout2->addWidget(num_ana);
                    layout2->addWidget(op_alg);
                    layout2->addWidget(opti);
                    layout2->addWidget(proba);
                    layout2->addWidget(quantum_alg);
                    layout2->addWidget(repr_theo);
                    layout2->addWidget(ring);
                    layout2->addWidget(spec);
                    layout2->addWidget(stat_theo_math);
                    layout2->addWidget(sympletic);
                }
                if(cs->isChecked())
                {
                    cs->setDisabled(true);
                    layout2->addWidget(title_cs);
                    layout2->addWidget(ai);
                    layout2->addWidget(comp_lang);
                    layout2->addWidget(complexity);
                    layout2->addWidget(cefs);
                    layout2->addWidget(comp_geo);
                    layout2->addWidget(cs_game_theo);
                    layout2->addWidget(vision_pattern);
                    layout2->addWidget(comp_socie);
                    layout2->addWidget(crypto);
                    layout2->addWidget(data);
                    layout2->addWidget(databases);
                    layout2->addWidget(library);
                    layout2->addWidget(discrete);
                    layout2->addWidget(dpcc);
                    layout2->addWidget(emerging);
                    layout2->addWidget(formal_lang);
                    layout2->addWidget(gene_lit);
                    layout2->addWidget(graphics);
                    layout2->addWidget(hardware);
                    layout2->addWidget(human_comp);
                    layout2->addWidget(info_retrie);
                    layout2->addWidget(info_theo_cs);
                    layout2->addWidget(logic_cs);
                    layout2->addWidget(mach_lear_cs);
                    layout2->addWidget(math_software_cs);
                    layout2->addWidget(multiagent);
                    layout2->addWidget(multimedia);
                    layout2->addWidget(network_int);
                    layout2->addWidget(neural_comp);
                    layout2->addWidget(num_anal);
                    layout2->addWidget(op_syst);
                    layout2->addWidget(o_cs);
                    layout2->addWidget(perf);
                    layout2->addWidget(programming);
                    layout2->addWidget(robot);
                    layout2->addWidget(social_net);
                    layout2->addWidget(soft_engi);
                    layout2->addWidget(sound_cs);
                    layout2->addWidget(symbol_cs);
                    layout2->addWidget(syst_control);
                }
                if(bio->isChecked())
                {
                    bio->setDisabled(true);
                    layout2->addWidget(title_bio);
                    layout2->addWidget(biomol);
                    layout2->addWidget(cell_beha);
                    layout2->addWidget(genom);
                    layout2->addWidget(mol_net);
                    layout2->addWidget(neuron);
                    layout2->addWidget(o_bio);
                    layout2->addWidget(pop_evol);
                    layout2->addWidget(quant_method);
                    layout2->addWidget(subcell);
                    layout2->addWidget(tissues);
                }
                if(fin->isChecked())
                {
                    fin->setDisabled(true);
                    layout2->addWidget(title_fin);
                    layout2->addWidget(comp_fin);
                    layout2->addWidget(econ_fin);
                    layout2->addWidget(gen_fin);
                    layout2->addWidget(math_fin);
                    layout2->addWidget(porto);
                    layout2->addWidget(price);
                    layout2->addWidget(risk);
                    layout2->addWidget(stat_fin);
                    layout2->addWidget(trade);
                }
                if(stat->isChecked())
                {
                    stat->setDisabled(true);
                    layout2->addWidget(title_stat);
                    layout2->addWidget(applications);
                    layout2->addWidget(compute);
                    layout2->addWidget(mach_lear_stat);
                    layout2->addWidget(method);
                    layout2->addWidget(o_stat);
                    layout2->addWidget(stat_theo);
                }
                if(elec->isChecked())
                {
                    elec->setDisabled(true);
                    layout2->addWidget(title_elec);
                    layout2->addWidget(audio);
                    layout2->addWidget(image);
                    layout2->addWidget(signal);
                }
                if(econ->isChecked())
                {
                    econ->setDisabled(true);
                    layout2->addWidget(title_econ);
                    layout2->addWidget(econometrics);
                    layout2->addWidget(general_economics);
                    layout2->addWidget(theoretical_econ);

                }
                // add the push button to the second layout and put the layout in the second window
                layout2->addWidget(val);
                precise->setLayout(layout2);

                // wait 10ms to avoid saturation
                delay();
                // Check if the button has been clicked. In this case, close the first window and open the second
                QObject::connect(validate_button, SIGNAL(clicked()), home, SLOT(close()));
                QObject::connect(validate_button, SIGNAL(clicked()), precise, SLOT(show()));
                // Break the loop if the second window is open
                if (precise->isHidden() != true)
                {
                    a = false;
                    if (physics->isChecked() != true and maths->isChecked() != true and cs->isChecked() != true and bio->isChecked() != true and fin->isChecked() != true and stat->isChecked() != true and elec->isChecked() != true and econ->isChecked() != true)
                    {

                        int ok = QMessageBox::critical(precise, "Interest selection error", "You have to select an interest.", QMessageBox::Ok);
                        if (ok == QMessageBox::Ok)
                        {
                            precise->close();
                            qApp->quit();
                        }
                    }
                }
            }

            bool b = true;

            // TO CODE AND COMMENT
            while (b)
            {
                QObject::connect(val, SIGNAL(clicked()), precise, SLOT(hide()));
                delay();
                if (precise->isHidden() == true)
                {
                    b = false;
                    precise->close();
                    info.update_info_user(checkboxes);
                }
            }
            }
        }
    return app.exec();
}


