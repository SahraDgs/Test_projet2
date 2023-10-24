OBJS = main.o Image.o Dataset.o MultiPerceptron.o Perceptron.o ImageClassifier.o
TARGET = classifier
CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: all clean run

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET) Data/mnist_images_train.csv Data/mnist_label_train.csv Data/mnist_images_test.csv Data/mnist_label_test.csv Data/mnist_labelnames.csv
runfruits: $(TARGET)
	./$(TARGET) Data/fruits_images_train.csv Data/fruits_label_train.csv Data/fruits_images_test.csv Data/fruits_label_test.csv Data/fruits_labelnames.csv

main.o: main.c Image.h Dataset.h ImageClassifier.h
Dataset.o: Dataset.c Dataset.h Image.h
Image.o: Image.c Image.h
ImageClassifier.o: ImageClassifier.c ImageClassifier.h Image.h Dataset.h \
  MultiPerceptron.h
MultiPerceptron.o: MultiPerceptron.c MultiPerceptron.h Perceptron.h
Perceptron.o: Perceptron.c Perceptron.h
