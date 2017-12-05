NAME=proj4

all: clean do

do: $(NAME).tex
	latex $(NAME).tex
	bibtex $(NAME)
	latex $(NAME).tex
	latex $(NAME).tex
	dvips $(NAME).dvi -t a4
	ps2pdf $(NAME).ps

clean:
	rm -f $(NAME).dvi $(NAME).log $(NAME).aux $(NAME).ps $(NAME).pdf