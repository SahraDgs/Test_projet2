#include <stdio.h>
#include <stdlib.h>

#include "Dataset.h"
#include "Image.h"

struct dataset_t
{
    char **labelNames; // The label names
    int nbLabels;      // The number of labels
    Image **images;    // The array of sketches
    int *labels;       // The array of labels
    int nbImages;      // The number of sketches
};

static void exitError(char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(-1);
}

Dataset *dsLoad(const char *imageFile, const char *labelFile, const char *labelnameFile)
{
    Dataset *ds = malloc(sizeof(Dataset));

    if (!ds)
        exitError("dsLoad: Impossible to allocate Dataset\n");

    // Extract the labels
    FILE *fp = fopen(labelnameFile, "r");
    if (!fp)
        exitError("dsLoad: Impossible to open labelnameFile\n");

    fscanf(fp, "%d", &(ds->nbLabels));

    char buffer[1000];
    fgets(buffer, 1000, fp);
    fgets(buffer, 1000, fp);

    ds->labelNames = malloc(ds->nbLabels * sizeof(char *));

    int indexLabel = 0;
    int i = 0;
    while (buffer[i] != '\n' && buffer[i] != '\0')
    {
        int j = i;
        while (buffer[j] != ' ' && buffer[j] != '\0' && buffer[j] != '\n')
            j++;
        ds->labelNames[indexLabel] = malloc((j - i + 1) * sizeof(char));
        for (int k = i; k < j; k++)
            ds->labelNames[indexLabel][k - i] = buffer[k];
        ds->labelNames[indexLabel][j - i] = '\0';
        indexLabel++;
        i = j + 1;
    }
    fclose(fp);

    // Extract the images

    fp = fopen(imageFile, "r");
    if (!fp)
        exitError("dsLoad: Impossible to open imageFile\n");

    fscanf(fp, "%d", &(ds->nbImages));

    int nbrows, nbcolumns;

    fscanf(fp, "%d", &nbrows);
    fscanf(fp, "%d", &nbcolumns);

    printf("Reading %d images of size %dx%d from '%s'...\n", ds->nbImages,
           nbrows, nbcolumns, imageFile);

    ds->images = malloc(ds->nbImages * sizeof(Image *));
    if (!ds->images)
        exitError("dsLoad: Impossible to allocate image array\n");

    int totalimgsize = nbrows * nbcolumns;
    unsigned char imgArray[totalimgsize];

    for (int i = 0; i < ds->nbImages; i++)
    {
        for (int j = 0; j < totalimgsize; j++)
            fscanf(fp, "%hhu", imgArray + j);

        ds->images[i] = imgCreate(nbrows, nbcolumns, imgArray);
    }

    fclose(fp);

    // Extract labels

    ds->labels = malloc(ds->nbImages * sizeof(int));
    if (!ds->labels)
        exitError("dsLoad: Impossible to allocate label array\n");

    fp = fopen(labelFile, "r");
    if (!fp)
        exitError("dsLoad: Impossible to open labelFile\n");
    int nblabels;
    fscanf(fp, "%d", &nblabels);
    if (nblabels != ds->nbImages)
    {
        exitError("dsLoad: number of labels does not match number of images\n");
    }
    for (int i = 0; i < ds->nbImages; i++)
        fscanf(fp, "%d", ds->labels + i);

    fclose(fp);

    return ds;
}

void dsFree(Dataset *dataset)
{
    if (!dataset)
        return;

    for (int i = 0; i < dataset->nbImages; i++)
        imgFree(dataset->images[i]);

    free(dataset->images);
    free(dataset->labels);
    free(dataset);
}

int dsGetNbImages(Dataset *dataset)
{
    return dataset->nbImages;
}

Image *dsGetImage(Dataset *dataset, int i)
{
    return dataset->images[i];
}

int dsGetLabel(Dataset *dataset, int i)
{
    return dataset->labels[i];
}

int dsGetNbLabelNames(Dataset *dataset)
{
    return dataset->nbLabels;
}

char *dsGetLabelName(Dataset *dataset, int label_index)
{
    return dataset->labelNames[label_index];
}
