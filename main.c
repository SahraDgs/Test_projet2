#include <stdio.h>
#include <time.h>

#include "Image.h"
#include "Dataset.h"
#include "ImageClassifier.h"

// CECI EST UN TEST

int main(int argc, char *argv[])
{
    int iarg = 1;
    int nbEpochs = 1;
    bool randomOrder = false;
    bool showErrors = false;
    char *filepath = NULL;

    // parsing command line arguments
    while (iarg < argc && argv[iarg][0] == '-')
    {
        switch (argv[iarg][1])
        {
        case 'e':
            nbEpochs = atoi(argv[++iarg]);
            break;
        case 'r':
            randomOrder = true;
            break;
        case 'p':
            showErrors = true;
            filepath = argv[++iarg];
        }
        iarg++;
    }

    if (iarg > argc || argv[iarg][0] == '-' || argc - iarg < 5)
    {
        fprintf(stderr, "%d %d\n", iarg, argc);
        fprintf(stderr, "Missing or wrong arguments\n");
        fprintf(stderr, "Usage: %s %s %s %s %s\n",
                argv[0], "[-e nb_epochs|-p bmp_directory|-r]",
                "train_image_file train_label_file",
                "test_image_file test_label_file",
                "labelnames_file");
        return EXIT_FAILURE;
    }

    Dataset *ls = dsLoad(argv[iarg], argv[iarg + 1], argv[iarg + 4]);

    printf("Training set with %d images of sizes %zux%zu and %d labels\n", dsGetNbImages(ls),
           imgGetNbRows(dsGetImage(ls, 0)), imgGetNbColumns(dsGetImage(ls, 0)), dsGetNbLabelNames(ls));

    Dataset *ts = dsLoad(argv[iarg + 2], argv[iarg + 3], argv[iarg + 4]);

    printf("Test set with %d images of sizes %zux%zu and %d labels\n", dsGetNbImages(ts),
           imgGetNbRows(dsGetImage(ts, 0)), imgGetNbColumns(dsGetImage(ts, 0)), dsGetNbLabelNames(ts));

    ImgClas *ic = icCreate(ls, icGetCustomFeatures);

    icPlotOnePerClass(ls);

    // to be removed if you want fix the random order
    srand(time(NULL));

    clock_t start, end, startts, endts;
    start = clock();
    icTrain(ic, nbEpochs, randomOrder, 1);
    end = clock();
    printf("Training time: %.2fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    start = clock();
    float errorls = icGetTestError(ic, ls);
    end = clock();
    startts = clock();
    float errorts = icGetTestError(ic, ts);
    endts = clock();
    printf("Error on the learning set: %f%% (cpu time:%.2f)\nError on the test set: %f%% (cpu time:%.2f)\n",
           errorls * 100, ((double)(end - start)) / CLOCKS_PER_SEC,
           errorts * 100, ((double)(endts - startts)) / CLOCKS_PER_SEC);

    if (showErrors)
        icShowErrors(ic, ts, filepath);

    dsFree(ls);
    dsFree(ts);
    icFree(ic);
}
