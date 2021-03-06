\name{listPeople}
\alias{listPeopleAsList}
\alias{listPeopleAsDataFrame}
\title{List content of address book example for ProtoBuf}
\description{
  These function provide two simple examples for using
  ProtoBuf generated accessor functions to import ProtoBuf data into R.
}
\usage{
  listPeopleAsList(filename, verbose=FALSE)
  listPeopleAsDataFrame(filename, verbose=FALSE)
}
\arguments{
  \item{filename}{complete path to a binary addressbook written in
    function built from the addressbook.proto description; an example
    file is used is no argument is supplied}
  \item{verbose}{optional boolean flag indicating verbose operation}
}
\value{For \code{listPeopelAsDataFrame}, a data.frame combining the id,name,email and
  id,phoneType,phoneNumber data sets. For \code{listPeopelAsList}, a
  nested list combining the id, name, email and
  phoneType, phoneNumber data sets.
}
\details{
  This function provides an implementation of the \code{list_people.cc} example
  provided with the ProtoBuf compiler.

  Protocol Buffers is a serialization format with an interface
  description language developed by Google. The original Google implementation
  for C++, Java and Python is available under the BSD license at
  \url{http://code.google.com/p/protobuf/}. A good description of
  Protocol Buffers is available at
  \url{http://en.wikipedia.org/wiki/Protocol_Buffers}. 

  This function is a first attempt of importing binary data from
  ProtoBuf files into R.
}
\author{Romain Francois and Dirk Eddelbuettel for the R package; Google for Protocal Buffers.}
\examples{
  print(listPeopleAsList())
  print(listPeopleAsDataFrame())
}

